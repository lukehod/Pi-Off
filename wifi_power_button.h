#ifndef WIFI_POWER_BUTTON_H
#define WIFI_POWER_BUTTON_H

/////////////////////////////////////////////////////////////////////////////////
// Configurable settings:
/////////////////////////////////////////////////////////////////////////////////

/*
 * Enter your wifi SSID and password below
 */
#define USRSSID  "your wifi ssid"
#define USRPSK   "your wifi password"

/* 
 * Set GPIO Pins (leave as default unless you know what you are doing)
 *    
 *    POWER_PIN - GPIO output pin to control on/off functionality
 *    LED_PIN - GPIO pin to control LED, default is on-board LED
 */
#define POWER_PIN 0; // GPIO0 D3
#define LED_PIN   2; // GPIO2 D4

/*
 * Adjust brightness of LED
 *    Set value between 1023 (lowest) to 0 (brightest)
 */
#define LED_BRIGHTNESS 0;

/* 
 * Uncomment both these lines to enable mDNS functionality: 
 */
//#define USE_MDNS
//#define MDNSNAME "wifipowerbutton"

/* 
 *  Uncomment to enable static IP. 
 *  Edit the IPAddress lines in the main file for your network settings.
 */
//#define USE_STATIC_IP


/////////////////////////////////////////////////////////////////////////////////
// DONT CHANGE ANYTHING PAST THIS POINT!
/////////////////////////////////////////////////////////////////////////////////

// Function declarations
void triggerPower(void);
void handleNotFound(void);
void handleLEDButtonPress(void);
void handlePowerButtonPress(void);
void handleBrightness(void);
void handleRoot(void);
void blinkLED(void);
void toggleLED(void);
void toggleBrightness(void);

// Include the html file
#include "index.h"

#endif
