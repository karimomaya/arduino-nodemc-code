#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

const char *ssid = "kareem-arduino";
const char *password = "123456789";

ESP8266WebServer server(80);

void handleRoot() {
    response();
}

const String HtmlHtml = "<html><head>"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /></head>";
const String HtmlHtmlClose = "</html>";
const String HtmlTitle = "<h1>List Of networks</h1><br/>\n";
const String formOpen = "<br/><form action=\"http://192.168.4.1/submit\" method=\"POST\">";
String comboBox = "<select name=\"wifiname\">";

const String passwordTxt =  "Password: <input type=\"text\" name =\"password\">";
const String buttonSubmit = "<input type=\"submit\" value=\"Submit\">";
const String formClose = "</form><br>";

void response(){
  String htmlRes = HtmlHtml + HtmlTitle;
  
  htmlRes += formOpen;
  htmlRes += comboBox;
  htmlRes += passwordTxt;
  htmlRes += buttonSubmit;
  htmlRes += formClose;
  
  htmlRes += HtmlHtmlClose;

  server.send(200, "text/html", htmlRes);
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

void setup() {
    delay(1000);
    Serial.begin(9600);
    Serial.println();

    WiFi.softAP(ssid, password);

    IPAddress apip = WiFi.softAPIP();
    Serial.print("visit: \n");
    Serial.println(apip);
    server.on("/", handleRoot);
    server.on("/submit", handleSubmit);
    server.begin();
    Serial.println("HTTP server beginned");
    listNetworks();
}

void listNetworks() {
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

  
  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    
    Serial.print(WiFi.SSID(thisNet));
    
    comboBox += "<option value=";
    comboBox += WiFi.SSID(thisNet);
    comboBox += ">";
    comboBox +=  WiFi.SSID(thisNet);
    comboBox += "</option>" ;
  }
  comboBox += "</select>";
}

void loop() {
    server.handleClient();
}
