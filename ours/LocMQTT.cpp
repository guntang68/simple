/*
 * LocMQTT.cpp
 *
 *  Created on: Oct 17, 2019
 *      Author: annuar
 */

#include <LocMQTT.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include <TimeLib.h>
#include <WiFi.h>

const char* mqtt_server = "103.75.190.251";
String message="";
String topic="";
char tempString[120];
char tempTopic[36];

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* message, unsigned int length);
void reconnect();

LocMQTT::LocMQTT() {
	log_i("================== LocMQTT::LocMQTT()=============");
	client.setServer(mqtt_server, 1883);
	client.setCallback(callback);
}


void LocMQTT::update() {
//	log_i("????A");
	if (!client.connected()) {
//		log_i("????B");
		delay(1000);
		reconnect();
	}
	else{
//		log_i("????C");
		client.loop();
	}
}

void LocMQTT::hantar(String t, String m) {
	topic = t;
	message = m;

	if(client.connected() && m.length()>0){
		m.toCharArray(tempString, m.length()+1);
		t.toCharArray(tempTopic, t.length()+1);
		client.publish(tempTopic, tempString);

	}
}

void callback(char* topic, byte* message, unsigned int length)
{
	String messageTemp;

	for (int i = 0; i < length; i++) {
		messageTemp += (char)message[i];
	}
	if (String(topic) == "esp32/output") {
		if(messageTemp == "on"){

			log_i("+++++++++++++++++++++++++++++++ON");
		}
		else if(messageTemp == "off"){
			log_i("+++++++++++++++++++++++++++++++OFF");
		}
		else{
			log_i("%s",messageTemp.c_str());
		}
	}
}

void reconnect()
{
	while (!client.connected() && WiFi.isConnected()) {
		yield();
		delay(20);
//		log_i("sini ke?");
		if (client.connect("ESP8266Client")) {
			client.subscribe("esp32/output");
			break;
		} else {
			delay(5000);
		}
	}
//	log_i("done ke?");
}

LocMQTT::~LocMQTT() {
}
