# Wifi Power Button for Raspberry Pi
Use an ESP8266-based arduino microcontroller ([D1 mini](https://docs.wemos.cc/en/latest/d1/d1_mini.html) by default) to remotely power on and off your Raspberry Pi from any device connected to your wireless network!

## How to get running:

### Parts needed:
* Raspberry Pi and correct power supply (I used a 4B, but should work with any version)
* LOLIN/Wemos D1 Mini or other ESP8266 or ESP32 based device (guide assumes D1 Mini, but minor changes would be needed for most other devices)
* Dupont cables or other wires and solder for wiring
* Micro-usb cable to connect D1 Mini to computer


### Setup the Raspberry Pi to use GPIO shutdown
1. Go to the command line on the RPi (ssh if on another system)
2. `sudo nano /boot/config.txt`
3. Scroll to bottom and add the following line:
  ```
  # Enable GPIO power trigger
  dtoverlay=gpio-shutdown
  ```
4. `crl+x`, `Y`, `enter` to save and exit the editor
5. `sudo reboot` to restart the system

### Install Arduino IDE and configure it to use D1 mini
1. Download the latest [Arduino IDE](https://www.arduino.cc/en/main/software) for your system if you don't already have it installed
2. Install [esp8266 with Boards Manager](https://github.com/esp8266/Arduino#installing-with-boards-manager) in the Arduino IDE
3. Open the IDE and go to `Tools`>`Boards` and select `Wemos D1 R2 & mini`
4. Make sure that `Tools`>`Upload Speed` is set to `115200` in order to be able to read the serial output correctly

### Upload the sketch for the D1 Mini

1. Go to the GitHub repository and click the green `Clone or download` button and then `Download ZIP` to download the needed files.

  > _OPTIONAL_: you can also fork the repository to your own GitHub account if you want to use source control on your own project.

2. Unzip the files to a folder on your computer
3. In the Arduino IDE goto `File`>`Open...` and select one of the files in the folder you unzipped (it should open the whole project no matter which you choose)
4. Go to `wifi_power_button.h` and change the following settings for your network:
   ```
  #define USRSSID  "your wifi ssid"
  #define USRPSK   "your wifi password"
  ```
  > _Optional_: Uncomment the appropriate lines in this file to enable mDNS and/or static IP if you would like.

5. Plug the D1 mini into your computer's USB port and hit the `Upload` button in the top right of the IDE to compile the code and upload it to your device.
6. Go to `Tools`>`Serial Monitor` and make sure it is set to `115200` in the bottom right corner of the Serial Monitor.
7. Once the code is uploaded to the D1 Mini, you can hit the reset button on the device and you should see your network info come up on the Serial Monitor once connected.
8. Type the IP address from the Serial Monitor into your web browser and you should see the webpage if everything is setup correctly

### Wire it all together
> A word of caution here: Incorrectly wiring the Raspberry Pi and/or the Wemos D1 Mini could ***permanently damage*** either devices! It is safest to do your wiring while there is no power connected and be sure to double check your connections to make sure you are not sending power to a pin that cannot handle it. I accept no liability for any damage from incorrect wiring!

![wiring diagram](/img/wifi_button_wiring.png)

Also refer to a pinout diagram for [Raspberry Pi](https://pinout.xyz/) and [D1 Mini](https://docs.wemos.cc/en/latest/d1/d1_mini.html) to make it easier to select the correct pins.
1. Connect `pin 3` on the Raspberry Pi to `pin D3` on the D1 Mini
2. Connect one of the 5V pins and one of the ground pins on the Raspberry Pi to the `5V` pin and `GND` on the D1 Mini.  (I use `pin 4` and `pin 6` on the RPi)
3. Double check that your setup is correct (especially that no 5V pin is connected to ground or an IO pin anywhere!) and then you can plug in the power cable for your Raspberry Pi to let it boot up.

### Test it out
After everything is up and running, go to the IP for the D1 mini (or the `.local` address if using mDNS) in a browser on any device connected to your home wifi. If you have not setup a static IP or mDNS, you may have to use a network analyser app to find the correct IP.

You should be able to see the hosted webpage at this point and you can test the LED button or the Power button to see how everything works!

### Troubleshooting
If you run into any problems, feel free to open an issue in the GitHub repository or [reach out to me](mailto:connect@lukehod.net) and I'll do my best to help!
