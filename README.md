# esp8266_homekit_temp
Small project to send data from a temperature sensor to a HomeKit server, running on a Raspberry Pi. Due to an analog temperature sensor being used, an esp8266 with analog support is required (I used a nodeMCU v1.0). A digital temperature sensor could also work directly either wired up to the Pi or another esp8266.

## Installation
Verify and upload the sketch to your board and take note of the IP Address displayed in the Serial Monitor. Go to `http://enter_ip_address/temperature` and ensure that there's a line of json looking like `{ "temperature" : 25 }`.

Next, install [Homebridge](https://github.com/nfarina/homebridge) along with the [homebridge-http-temperature](https://www.npmjs.com/package/homebridge-http-temperature) plugin. Configure the Homebridge config to include the accessory:

```
"accessories": [
   {
       "accessory": "HttpTemperature",
       "name": "Temperature",
       "url": "http://192.168.1.35/temperature?format=json",
       "http_method": "GET"
      }
   ],
```

After starting [Homebridge](https://github.com/nfarina/homebridge) the current temperature should now be displayed in your Home app! (see below for images).

## Images
### Home App
![Home App](https://github.com/greenywd/esp8266_homekit_temp/blob/master/Home_screenshot.png)

### nodeMCU wired up to the sensor on a breadboard
![nodeMCU on breadboard](https://github.com/greenywd/esp8266_homekit_temp/blob/master/nodeMCU_breadboard.jpg)
