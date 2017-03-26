#ifndef _OPEN_ROBOT_H_

#define _OPEN_ROBOT_H_
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <FS.h>
#define RCONFIG_VER						0x01
#define RCONFIG_ENABLE_AP				0x01
#define RCONFIG_FIXED_AP_IP				0x02
#define RCONFIG_ENABLE_AP_IF_NO_STA		0x04
#define RCONFIG_ENABLE_STA				0x08
#define RCONFIG_FIXED_STA_IP			0x10

#define RECONFIG_DEF_AP_NAME		 ((char *)"kareem-arduino")
#define RECONFIG_DEF_AP_PASSWORD	 ((char *)"123456789")	

struct RConfig{
	int  ver;
	int  flags;
	char STAName[16];//wifiName
	char STAPassword[16];
	char APName[16];
	char APPassword[16];
	IPAddress STAIP;
	IPAddress APIP;
};

class RServer{
	
public: 
	RServer(int port);
	
	void begin();
	void handleClient();

	void setupServer();

	void close();
	void stop();
  	void openDirectory();
private:

	ESP8266WebServer 		webServer;
	ESP8266HTTPUpdateServer	updateServer;
	RConfig 				config;
	
	bool loadConfig(RConfig& config);
	void saveConfig(RConfig& config);
	
	void registerRequestHandlers();

	static RServer* pThis;
	static void handleRoot();
	static void handleWifiSubmittion();
	static void handleSaveConfig();
	static void handleGetConfig();
	static void stopAP();
	
	String listAvailableWIFI();
	bool checkPermission();
	
	IPAddress configureAP(RConfig& config);
	bool connectSTA(RConfig& config);
	
	void logging(const char* msg);
};

#endif 