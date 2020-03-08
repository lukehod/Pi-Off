#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "wifi_power_button.h"


/////////////////////////////////////////////////////////////////////////////////
// Variable setup
/////////////////////////////////////////////////////////////////////////////////

// Variables defined in wifi_power_button.h
const char* ssid     = USRSSID;
const char* password = USRPSK;
const int   pin      = POWER_PIN;
const int   led      = LED_PIN;
const int   led_brightness = LED_BRIGHTNESS;

// Change these values if using static IP for project (see wifi_power_button.h)
#ifdef USE_STATIC_IP 
  const IPAddress ip(192, 168, 1, 110);
  const IPAddress gateway(192, 168, 1, 1);
  const IPAddress subnet(255, 255, 255, 0);
  const IPAddress dns(192, 168, 1, 1);
#endif

// Set LED to be on or off at start (default is off)
bool status = false;

// Create server instance
ESP8266WebServer server(80);


/////////////////////////////////////////////////////////////////////////////////
// Main functions
/////////////////////////////////////////////////////////////////////////////////

//
// Setup
// 
void setup(){
  // Prepare GPIO pins
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  pinMode(led, OUTPUT);
  analogWrite(led, 1024); // off initially

  // Start serial monitor
  Serial.begin(115200);
  delay(10);
  
  Serial.println("===========================");
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Configure wifi and optionally the static IP
  #ifdef USE_STATIC_IP 
    WiFi.config(ip, gateway, subnet, dns);
  #endif
  WiFi.begin(ssid, password);

  // Connect to wifi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());

  // Setup mDNS if enabled
  #ifdef USE_MDNS
    if (MDNS.begin(MDNSNAME)) {
      Serial.println("MDNS responder started");
      Serial.print("Server accessable at: http://");
      Serial.print(MDNSNAME);
      Serial.println(".local");
    }
  #endif

  // Setup server
  server.on("/", handleRoot);
  server.on("/power", handlePowerButtonPress);
  server.on("/led", handleLEDButtonPress);
  server.onNotFound(handleNotFound);
  server.begin();
  
  Serial.println("HTTP server started");
  Serial.println();
  Serial.println("===========================");
}


//
// Loop
//
void loop(void) {
  server.handleClient();
  #ifdef USE_MDNS
    MDNS.update();
  #endif
}



/////////////////////////////////////////////////////////////////////////////////
// Server functions
/////////////////////////////////////////////////////////////////////////////////


//
// Root handler
//
void handleRoot() {
  String s = MAIN_page;
  server.send(200, "text/html", s); // use html defined in index.h
}


//
// Power button handler
//
void handlePowerButtonPress() {
  triggerPower();
  blinkLED();
  server.sendHeader("Location", "/", true);   // Redirect home  
  server.send(302, "text/plane","");
}


//
// LED button handler
//
void handleLEDButtonPress() {
  toggleLED();
  server.sendHeader("Location", "/", true);   // Redirect home  
  server.send(302, "text/plane","");
}


//
// 404 handler
//
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}



/////////////////////////////////////////////////////////////////////////////////
// Helper functions
/////////////////////////////////////////////////////////////////////////////////


//
// Pulls the pin to ground briefly to simulate a button push
//
void triggerPower() {
  Serial.println("POWER BUTTON HIT\n");
  digitalWrite(pin, LOW);
  delay(150);
  digitalWrite(pin, HIGH);
}


//
// Blinks the LED off or on depending on led status
//
void blinkLED() {
  analogWrite(led, (status ? 1024 : led_brightness)); 
  delay(150);
  analogWrite(led, (status ? led_brightness : 1024));
}


//
// Turns LED on or off
//
void toggleLED() {
  analogWrite(led, (status ? 1024 : led_brightness));   // OFF : ON
  status = !status;
}
