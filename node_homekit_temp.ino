#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

const char* ssid = "INSERT NETWORK SSID HERE";
const char* password = "INSERT NETWORK PASSWORD HERE";

ESP8266WebServer server(80);
DHT dht(D2, DHT22); 

void handleRoot() {
  server.send(200, "text/plain", "This is the server root. Nothing to see here...");
}

void handleNotFound(){
  server.send(404, "text/plain", "404 Not Found.");
}

void setup(){
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  dht.begin();
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("Connected to: " + String(ssid));
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", handleRoot);
  
  server.on("/temperature", [](){
      
      char json[128];
      snprintf(json, sizeof(json), "{\n \"temperature\":%i,\n \"humidity\":%i\n}", round(dht.readTemperature()), round(dht.readHumidity()));
      Serial.println("Page accessed...");
      
    server.send(200, "application/json", json);
  });
  
  server.onNotFound(handleNotFound);

  server.begin();
}

void loop(){
  server.handleClient();

  delay(1000);
}
