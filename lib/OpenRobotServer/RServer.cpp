#include <RServer.h>

RServer* RServer::pThis = NULL;
RServer::RServer(int port):webServer(port){

	delay(1000);// is this required?
	pThis = this;
	
	updateServer.setup(&webServer);
}

void RServer::setupServer() {
	openDirectory();
	
	loadConfig(config);
	
	bool bconnected=false;
	if(config.flags & RCONFIG_ENABLE_STA)
		bconnected = connectSTA(config);
	if(config.flags & RCONFIG_ENABLE_AP || (!bconnected && (config.flags & RCONFIG_ENABLE_AP_IF_NO_STA)))
		configureAP(config);

	registerRequestHandlers();
	begin();
}

void RServer::begin(){
	webServer.begin();
}

void RServer::handleClient(){
	webServer.handleClient();
}

void RServer::close(){
	webServer.close();
}

void RServer::stop(){
	webServer.stop();
}

//try to load config from config file if can't load default config
bool RServer::loadConfig(RConfig& config){
	
	if(SPIFFS.exists("/config.txt")){
		File file = SPIFFS.open("/config.txt", "r");
		file.read((uint8_t*)&config, sizeof(RConfig));
		file.close();
		return true;
	}
	return false;
}

//save config to config file
void RServer::saveConfig(RConfig& config){
	File file = SPIFFS.open("/config.txt", "w");
	file.write((uint8_t*)&config, sizeof(RConfig));
	file.close();
}

// to open data folder
void RServer::openDirectory() {
	SPIFFS.begin();
    Dir dir = SPIFFS.openDir("/");
}


void RServer::registerRequestHandlers(){

	webServer.on("/", pThis->handleRoot);
	
    webServer.on("/submit", pThis->handleWifiSubmittion);
	
    webServer.on("/list_wifi", HTTP_GET, [](){
		  if(!(pThis->checkPermission()))
			return;

		  String json = pThis->listAvailableWIFI();
		  pThis->webServer.send(200, "text/json", json);
		  json = String();
    });
}

String RServer::listAvailableWIFI() {
	logging("** Scan Networks **");
	
    int numSsid = WiFi.scanNetworks();
    if (numSsid == -1) {
    	logging("Couldn't get a wifi connection");
        return "[]";
    }
	
    String json = "[";  
    for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    
      logging(WiFi.SSID(thisNet).c_str());
      
      if (thisNet != 0)
		json += "},";
      
	  json += "{\"name\":\""+WiFi.SSID(thisNet)+"\"";
    }

    json += "}]";
	
    return json;
}


void RServer::handleRoot() {
	if(!(pThis->checkPermission()))
			return;
		
	File file = SPIFFS.open("/index.html", "r");
	size_t sent = pThis->webServer.streamFile(file, "text/html");
	file.close();//??
}

void RServer::handleWifiSubmittion() {
	if(!(pThis->checkPermission()))
			return;
		
	if (pThis->webServer.args() < 2 ) 
		return;
    
    for ( uint8_t i = 0; i < pThis->webServer.args(); i++ ) {
      if (pThis->webServer.argName(i) == "wifiname") {
		strcpy(pThis->config.STAName, pThis->webServer.arg(i).c_str());
      }
      else if (pThis->webServer.argName(i) == "password") {
      	strcpy(pThis->config.STAPassword, pThis->webServer.arg(i).c_str());
      }
    }

    pThis->stopAP();
    pThis->connectSTA(pThis->config);
    pThis->registerRequestHandlers();
 
}

void RServer::stopAP() {
	pThis->stop();
	WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
}

//update config and save config file
void RServer::handleSaveConfig(){
	if(!pThis->checkPermission())
		return;
	
}

//send RConfig as json + wifilist to select from
void RServer::handleGetConfig(){
	if(!pThis->checkPermission())
		return;
	
}


IPAddress RServer::configureAP(RConfig& config){

	WiFi.softAP(pThis->config.STAName, pThis->config.STAPassword);
  	return WiFi.softAPIP();
}

//if connected to wifi return true
bool RServer::connectSTA(RConfig& config){
	WiFi.mode(WIFI_STA);
	WiFi.begin(pThis->config.STAName, pThis->config.STAPassword);
   	while (WiFi.status() != WL_CONNECTED) {
    	delay(500);
    	Serial.print(".");
   	}
   	Serial.println(WiFi.localIP());
	return true;
}

bool RServer::checkPermission(){
	return true;
}
void RServer::logging(const char* msg){
	Serial.println(msg);
}