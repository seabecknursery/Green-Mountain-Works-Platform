#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <ArduinoJson.h>
#include <FS.h>

// Set your access point network credentials
const char* ssid = "Green Mountain Works Controller";
const char* password = "123456789";

AsyncWebServer server(80);

void setup() {
   // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();

  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });

  // Route to load style.css file
  server.on("/css/gmw.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/css/gmw.css", "text/css");
  });

   // Route to load style.css file
  server.on("/img/logo.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/img/logo.png");
  });
  
    // Route to load style.css file
  server.on("/js/gmw.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/js/gmw.js", "text/javascript");
  });

  // Start server
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}
