#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

#define WIFI_SSID "WIFI SSID"
#define WIFI_PASSWORD "WIFI PASSWORD"

// create an instance of the webserver on port 80 (ESP8266 can barely do SSL) 
ESP8266WebServer server(80);

// create an instance using the Adafruit DHT Library, configuring the pin and type of sensor
DHT dht(D2, DHT22); 

// function to handle the root of webserver - not needed but is nice to have
void handleRoot() {
  server.send(200, "text/plain", "This is the server root. Nothing to see here...");
}

// function to handle any page that the webserver doesn't offer, resulting in a 404 
// again not needed, but nice to have
void handleNotFound(){
  server.send(404, "text/plain", "404 Not Found.");
}

void setup(){

  // set the baud rate to 9600
  Serial.begin(9600);

  // if the SSID saved does not match the one stored in NVRAM (i think :p), connect to new SSID
  // otherwise print saying we found wifi creds!
  if (WiFi.SSID() != WIFI_SSID){
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  } else { 
    Serial.println("Previous Wifi credientials found!"); 
  }
  
  // begin logging of the DHT sensor
  dht.begin();
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // once connected, print SSID, and IP address of this device
  Serial.println("Connected to: " + String(WIFI_SSID));
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  // defining the root of the webserver
  server.on("/", handleRoot);
  
  // setup the page located at /temperature
  server.on("/temperature", [](){
      
      // create a char to 
      char json[128];
      snprintf(json, sizeof(json), "{\n \"temperature\":%i,\n \"humidity\":%i\n}", round(dht.readTemperature()), round(dht.readHumidity()));
      
      // print to serial that the page was accessed
      Serial.println("Page accessed...");
      
    server.send(200, "application/json", json);
  });
  
  // this calls the handleNotFound() function - if a page that isn't found is accessed
  server.onNotFound(handleNotFound);

  // start the web server!
  server.begin();
}

void loop(){

  // don't actually know what this does because there's no documentation on it
  // presumably handles the client accessing pages
  server.handleClient();

  delay(1000);
}
