/*
 * ConnectionObserver.h
 *
 * Control signal RGB LED based on MQTT and AP Status
 *
 *  Created on: 5 Aug 2022
 *      Author: jondurrant
 */

#ifndef SRC_CONNECTIONOBSERVER_H_
#define SRC_CONNECTIONOBSERVER_H_

#include "MQTTAgentObserver.h"
#include "RGBLEDAgent.h"

class ConnectionObserver : public  MQTTAgentObserver{
public:
	/***
	 * constructor
	 * @param p - LED Agent to manage LED
	 */
	ConnectionObserver(RGBLEDAgent * p);

	/***
	 * Destructor
	 */
	virtual ~ConnectionObserver();

	/***
	 * MQTT is offline, set LED to Amber
	 */
	virtual void MQTTOffline();

	/***
	 * MQTT is online, set LED to Blue
	 */
	virtual void MQTTOnline();

	/***
	 * Data send, do a single blink in Green
	 */
	virtual void MQTTSend();

	/***
	 * Data received, do a signle BLink in Red
	 */
	virtual void MQTTRecv();

	/***
	 * AP Link is down, set LED to Red
	 */
	void LinkDown();

	/***
	 * Access point joined, set LED to Green
	 */
	void APJoined();

	/***
	 * AP Link has failed, Blink Red
	 */
	void LinkFailed();

private:
	//LED Agent
	RGBLEDAgent * pRGBAgent = NULL;
};

#endif /* SRC_CONNECTIONOBSERVER_H_ */
