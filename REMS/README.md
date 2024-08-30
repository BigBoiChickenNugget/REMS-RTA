# REMS

The REMS system has two versions: an Arduino MEGA with a W5500 shield and an ESP32 with a W5500 module. The ESP32 version is the most recent and is currently under development.

### Installation

1. **Arduino Ethernet Library**: Download and install the Arduino Ethernet library. Ensure that you have the correct port specified in both directories' upload scripts.
2. **ESP32 Board Manager**: Install the ESP32 board manager to enable support for ESP32 boards.
3. **Modify Ethernet Library**: Update the Ethernet library to ensure compatibility with the ESP32. Locate the `Ethernet.h` file in the Arduino Ethernet library and change:

``` cpp
class EthernetServer : PublicServer
```
   to
``` cpp
class EthernetServer : public Print
```

4. **Upload Scripts**: Update the upload scripts to reflect the correct IP address as per your network configuration. 

5. **Upload**: Proceed with uploading the updated code to the respective boards.

### Usage

- **Web Interface**: The web page currently features two buttons for turning power and water off. Clicking these buttons will display text indicating that the power and water have been turned off, but this functionality does not yet interact with the hardware.
- **Temperature Control**: An input box allows you to set the desired temperature. If the current temperature (measured by the attached sensors) is below the desired value, the heat lamp ("furnace") is activated. Otherwise, the cooling fan is turned on. A JavaScript function in the code collects input from the web interface and sends it to the REMS board via a POST request.

### Further Areas of Development

1. **Dynamic Updates**: The current setup refreshes the web page every 5 seconds to show updates. It would be more efficient to use AJAX to dynamically update the page with sensor readings and other variables. Research AJAX for integrating dynamic updates into the webpage, or consider using a different web server library that supports dynamic content more effectively.

2. **Sensor Configuration Integration**: The [sensor configuration program](https://github.com/BigBoiChickenNugget/REMS-sensor-configuration) should be integrated with the REMS codebase. This integration will allow users to configure sensors directly without needing access to the codebase or the host computer. Note that the sensor configuration program modifies REMS board code, so the REMS code style must be maintained. Future updates to the sensor configuration program should align with the types of sensors being used.

