
#ifndef _OPEN_ROBOT_H_

#define _OPEN_ROBOT_H_

#define RCONFIG_ENABLE_AP				1
#define RCONFIG_FIXED_AP_IP				2
#define RCONFIG_ENABLE_AP_IF_NO_STA		4
#define RCONFIG_ENABLE_STA				8
#define RCONFIG_FIXED_STA_IP			16

#define RECONFIG_DEF_AP_NAME		"kareem-arduino"
#define RECONFIG_DEF_AP_PASSWORD	"123456789"	

struct RConfig{
	int  flags;
	char STAName[16];
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

	void close();
	void stop();
  
private:

	ESP8266WebServer 		webServer;
	ESP8266HTTPUpdateServer	updateServer;
	
	void loadConfig(RConfig& config);
	void saveConfig(RConfig& config);
	
	static RServer* pThis;
	static void handleRoot();
	static void handleSaveConfig();
	static void handleGetConfig();
	
	bool checkPermission();
	
	IPAddress configureAP(RConfig& config);
	bool connectSTA(RConfig& config);
	
	void logging(String msg);
};

#endif 