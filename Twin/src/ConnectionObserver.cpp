/*
 * ConnectionObserver.cpp
 *
 * Control signal RGB LED based on MQTT and AP Status
 *
 *  Created on: 5 Aug 2022
 *      Author: jondurrant
 */

#include "ConnectionObserver.h"

/***
* constructor
* @param p - LED Agent to manage LED
*/
ConnectionObserver::ConnectionObserver(RGBLEDAgent * p) {
	pRGBAgent = p;
}


/***
 * Destructor
 */
ConnectionObserver::~ConnectionObserver() {
	// NOP
}

/***
 * MQTT is offline, set LED to Amber
 */
void ConnectionObserver::MQTTOffline(){
	pRGBAgent->set(RGBModeOn, 0xFF, 0xBF, 0x00);
}

/***
 * MQTT is online, set LED to Blue
 */
void ConnectionObserver::MQTTOnline(){
	pRGBAgent->set(RGBModeOn, 0x00, 0x00, 0xFF);
}

/***
 * Data send, do a single blink in Green
 */
void ConnectionObserver::MQTTSend(){
	pRGBAgent->set(RGBModeOnce, 0x00, 0xFF, 0x00);
}

/***
 * Data received, do a signle BLink in Red
 */
void ConnectionObserver::MQTTRecv(){
	pRGBAgent->set(RGBModeOnce, 0xFF, 0x00, 0x00);
}

/***
 * AP Link is down, set LED to Red
 */
void ConnectionObserver::LinkDown(){
	pRGBAgent->set(RGBModeOn, 0xFF, 0x00, 0x00);
}

/***
 * Access point joined, set LED to Green
 */
void ConnectionObserver::APJoined(){
	pRGBAgent->set(RGBModeOn, 0x00, 0xFF, 0x00);
}

/***
 * AP Link has failed, Blink Red
 */
void ConnectionObserver::LinkFailed(){
	pRGBAgent->set(RGBModeSlow, 0xFF, 0x00, 0x00);
}
