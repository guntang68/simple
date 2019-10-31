/*
 * LocMQTT.h
 *
 *  Created on: Oct 17, 2019
 *      Author: annuar
 */

#ifndef OURS_LOCMQTT_H_
#define OURS_LOCMQTT_H_

#include "Arduino.h"
#include <PubSubClient.h>
#include <WiFiClient.h>
#include <TimeLib.h>
#include <WiFi.h>

class LocMQTT {
public:
	LocMQTT();
	virtual ~LocMQTT();
	void update();
	void hantar(String t, String m);
};

#endif /* OURS_LOCMQTT_H_ */
