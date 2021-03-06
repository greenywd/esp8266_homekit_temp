# esp8266_homekit_temp
Small project to send data from a temperature sensor to a HomeKit server, running on a Raspberry Pi. This branch supports the DHT22 Temperature and Humidity Sensor. See the schematic below on to setup the hardware side of it (I used a 10kohm resistor).

## Installation (DHT22)
Firstly, this sketch includes the [Adafruit DHT Library](https://github.com/adafruit/DHT-sensor-library)(Too lazy to write my own code atm :p). Make sure you have that installed before doing anything else.

Verify and upload the sketch to your board and take note of the IP Address displayed in the Serial Monitor. Go to `http://enter_ip_address/temperature` and ensure that there's json looking like 

```
{ 
   "temperature":25, 
   "humidity":30 
}
```

Next, install [Homebridge](https://github.com/nfarina/homebridge) along with the [homebridge-httptemperaturehumidity](https://www.npmjs.com/package/homebridge-httptemperaturehumidity) plugin. Configure the Homebridge config to include the accessory:

```
"accessories": [
   {
       "accessory": "HttpTemphum",
       "name": "Temperature",
       "url": "http://ESP_IP_HERE/temperature?format=json",
       "http_method": "GET"
   }
],
```

After starting [Homebridge](https://github.com/nfarina/homebridge) the current temperature and humidity should now be displayed in your Home app! (see below for images).

## Installation (Analog Sensor)
To-Do


## Images
### Home App
![Home App](https://github.com/greenywd/esp8266_homekit_temp/blob/master/Home_screenshot.png)

### Schematic
![Schematic](https://github.com/greenywd/esp8266_homekit_temp/blob/master/Hardware_config.png)
