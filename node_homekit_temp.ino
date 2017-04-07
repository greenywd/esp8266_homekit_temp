#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "INSERT NETWORK SSID HERE";
const char* password = "INSERT NETWORK PASSWORD HERE";

//connect center pin of temp sensor to A0
//connect other pins respectively (usually 5v and gnd)
int tempSensorPin = A0; 

ESP8266WebServer server(80);

int getTemperature(){
 //getting the voltage reading from the temperature sensor
 int sensorReading = analogRead(tempSensorPin);  
 
 // convert reading to voltage, multiply by 3.3 if 3.3v, 5 if 5v
 // as esp8266 will literally die if we use 5v, 3.3 is being used
 float voltage = sensorReading * 3.3;
 voltage /= 1024.0;

 // this is in celsius, so change to fahrenheit if needed
 float temperature = (voltage - 0.5) * 100;
 return round(temperature);
}

void handleRoot() {
  server.send(200, "text/plain", "This is the server root. Nothing to see here...");
}

void handleNotFound(){
  server.send(404, "text/plain", "404 Not Found.");
}

void setup(void){
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("Connected to: " + String(ssid));
  Serial.println("IP address: ");
  Serial.print(WiFi.localIP());
  
  server.on("/", handleRoot);
  
  server.on("/temperature", [](){
      int currentTemp = getTemperature();
      
      char json[128];
      snprintf(json, sizeof(json), "{\"temperature\":%i}", currentTemp);
      
    server.send(200, "application/json", json);
  });
  
  server.onNotFound(handleNotFound);

  server.begin();
}

void loop(){
  server.handleClient();

  delay(1000);
}
