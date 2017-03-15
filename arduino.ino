#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <FS.h>

const char *ssid = "kareem-arduino";
const char *password = "123456789";
boolean ifAP = true;

ESP8266WebServer server(80);

void handleRoot() {
    response();
}

void response(){
  File file = SPIFFS.open("/index.html", "r");
  size_t sent = server.streamFile(file, "text/html");

  Serial.println(sent);
  file.close();
}

void handleSubmit() {
  if (server.args() > 0 ) {
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      Serial.println(server.argName(i));
      Serial.println(server.arg(i));
   }
}
  response();
}

void openDirectory(){
   SPIFFS.begin();
    {
      Dir dir = SPIFFS.openDir("/");
      while (dir.next()) {    
        String fileName = dir.fileName();
        size_t fileSize = dir.fileSize();
        Serial.println(fileName);
      }
    }
}

IPAddress configureAP(){
  WiFi.softAP(ssid, password);
  return WiFi.softAPIP();
}

void logging(String msg) {
  Serial.println(msg);
}

void setup() {
    delay(1000);
    Serial.begin(9600);
    
    logging("Setup began");
    
    IPAddress apip = configureAP();
    
    openDirectory();

    
    server.on("/", handleRoot);
    server.on("/submit", handleSubmit);
    server.on("/list_wifi", HTTP_GET, [](){
      String json = listNetworks();
      server.send(200, "text/json", json);
      json = String();
    });
    
    server.begin();
    
    logging("HTTP server beginned");
    
}

String listNetworks() {
      // scan for nearby networks:
      Serial.println("** Scan Networks **");
      int numSsid = WiFi.scanNetworks();
      if (numSsid == -1) {
        Serial.println("Couldn't get a wifi connection");
        while (true);
      }

      // print the list of networks seen:
      Serial.print("number of available networks:");
      Serial.println(numSsid);

      String json = "[";
      // print the network number and name for each network found:
      for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    
      Serial.print(WiFi.SSID(thisNet));
      
      if (thisNet == 0) {
        json += "{\"name\":\""+WiFi.SSID(thisNet)+"\"";
      }
      else {
        json += "},{\"name\":\""+WiFi.SSID(thisNet)+"\"";
      }
    
    }

    json += "}";
      
    return json;
}

void loop() {
    server.handleClient();
}
