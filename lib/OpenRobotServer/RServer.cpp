#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <FS.h>
#include <RServer.h>

RServer* RServer::pThis = NULL;
RServer::RServer(int port):webServer(port){
	 updateServer.setup(&webServer);
	 pThis = this;
	 
	 RConfig config;
	 loadConfig(config);
	 
	 bool bconnected=false;
	 if(config.flags & RCONFIG_ENABLE_STA)
		 bconnected = connectSTA(config);
	 if(config.flags & RCONFIG_ENABLE_AP || (!bconnected && (config.flags & RCONFIG_ENABLE_AP_IF_NO_STA)))
		 configureAP(config);
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
void RServer::loadConfig(RConfig& config){
	
	
}

//save config to config file
void RServer::saveConfig(RConfig& config){
	
}

//handle '/' request and sent index.html
void RServer::handleRoot(){
	if(!pThis->checkPermission())
		return;
	
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
	
}

//if connected to wifi return true
bool RServer::connectSTA(RConfig& config){
	
	return true;
}

bool checkPermission(){
	return true;
}
void RServer::logging(String msg){
	
}