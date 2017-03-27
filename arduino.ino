#include <RServer.h>

RServer server(80);

void setup() {
  
  Serial.begin(9600);
  server.setupServer();
  
}

void loop() {
  server.handleClient();
}
