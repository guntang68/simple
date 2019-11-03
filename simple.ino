#include "Arduino.h"
#include <LocSpiff.h>
#include <LocWiFi.h>
#include <LocMQTT.h>
#include <LocDirectOTA.h>
#include <ArduinoJson.h>

//test

LocWiFi			*locWiFi;
LocMQTT			*locMqtt;
LocDirectOTA	*locDirectOTA;

int gValWiFi = lw_wifi_off;
int gValDirectOTA = 0;
String gMAC = "";

void _setupSPIFFiles(bool format);

// for MQTT
void _tickNyamuk();
time_t gtickNyamukTime = 0;
bool gtockBeat;
bool gmqttEnabled=true;

//=================================================================================================
void setup()
{
	Serial.begin(912600, SERIAL_8N1, 3, 1);
	delay(300);
	log_i("\n\n\n\nSalam Dunia dari %s\n\n\n\n", __FILE__);
	log_i("Memory = %d", String(esp_get_free_heap_size()).c_str());
	//	Memory = 1073447996

	_setupSPIFFiles(false);	//if true -> delete all files & create default file

	locWiFi = new LocWiFi(0,3000, &gValWiFi);
	gValWiFi = lw_wifi_apsta;
	//	Memory = 1073426524

	while(WiFi.macAddress().length() < 5){
		delay(500);
	}
	gMAC = WiFi.macAddress();
	log_i("------------------------------MAC = %s", gMAC.c_str());

	locMqtt = new LocMQTT(&gMAC);

	locDirectOTA = new LocDirectOTA(0,10, &gValDirectOTA);

}

//=================================================================================================
void loop()
{
//Add your repeated code here

	delay(500);

	_tickNyamuk();
}

//=================================================================================================
inline void _tickNyamuk() {
	locMqtt->update();
	if((millis()-gtickNyamukTime) > 60000){
		gtickNyamukTime = millis();
		gtockBeat = !gtockBeat;
		locMqtt->hantar(gMAC, gtockBeat?"1":"0");
		log_i("beat ---------------------------------> %s", gMAC.c_str());
	}
}
//=================================================================================================
inline void _setupSPIFFiles(bool format) {
	LocSpiff 	*locSpiff;
	FileInfo_t	info;

	locSpiff = new LocSpiff("_setupSPIFFiles");
	locSpiff->listAllFiles();
	if(format){
		log_i("deleting files ...");
		locSpiff->format();
		log_i("all files deleted");

		//create time stamp file for Online OTA
		locSpiff->appendFile("/timestamp.txt", "NONE");

		//create SSID credentials
		locSpiff->appendFile("/ssid.txt", "sta,ideapad,sawabatik1\n");
		locSpiff->appendFile("/ssid.txt", "sta,AndroidAP,sawabatik\n");
		locSpiff->appendFile("/ssid.txt", "sta,GF_Wifi_2.4GHz,Gr33nF1nd3r2018\n");
//		locSpiff->appendFile("/ssid.txt", "ap,NiNe,AsamBoiqqq\n");
		locSpiff->appendFile("/ssid.txt", "ap,GreenFinderIOT,0xadezcsw1\n");

		log_i("Default files created");
	}
	delete locSpiff;

	// Sistem will halt if format==true
	if(format){
		log_i("\n\n\n\n\n\n\n\n\nSistem Halt: Please change set SPIFF -> false\n\n\n");
		while(true){
			delay(100);
		}
	}
}

