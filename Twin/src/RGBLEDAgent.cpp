/*
 * RGBLEDAgent.cpp
 *
 * This is a task class to manage an RGB led. Common Cathode
 *
 *  Created on: 2 Aug 2021
 *      Author: jondurrant
 */

#include "FreeRTOS.h"
#include "RGBLEDAgent.h"
#include <stdio.h>
#include <cstring>

/***
 * Destructor
 */
RGBLEDAgent::~RGBLEDAgent() {
	if (xRGBQueue != NULL){
		vQueueDelete( xRGBQueue );
	}
}

/***
 * Construct an RGB LED Agent to manage LED colour
 * PINS are GPIO Pins for the Common Cathode LED
 * @param redPin
 * @param greenPin
 * @param bluePin
 */
RGBLEDAgent::RGBLEDAgent(const char *name, uint8_t redPin, uint8_t greenPin, uint8_t bluePin){
	rgbPWM.setup(redPin, greenPin, bluePin);
	strcpy(pName, name);
}

/***
 * Queue a change to the LED mode and colour
 * 8 bit colour used
 * @param m - Mode
 * @param r - Red
 * @param g - Green
 * @param b - Blue
 * @return
 */
BaseType_t RGBLEDAgent::set(RGBMode m, uint8_t r, uint8_t g, uint8_t b){
	uint8_t cmd[4];
	cmd[0] = m;
	cmd[1]= r;
	cmd[2] = g;
	cmd[3] = b;

	if (xRGBQueue != NULL){
		return xQueueSendToBack( xRGBQueue,
				( void * ) cmd,
				( TickType_t ) 10
			);
	}
	return -1;
}

/***
 *  create the vtask
 *  */
bool RGBLEDAgent::start(UBaseType_t priority){
	BaseType_t xReturned;
	printf("Start\n");
	xRGBQueue = xQueueCreate( 10, sizeof( uint8_t[4] ) );
	if (xRGBQueue != NULL){
		/* Create the ta
		 * sk, storing the handle. */
		xReturned = xTaskCreate(
			RGBLEDAgent::vTask,       /* Function that implements the task. */
			pName,   /* Text name for the task. */
			200,             /* Stack size in words, not bytes. */
			( void * ) this,    /* Parameter passed into the task. */
			priority,/* Priority at which the task is created. */
			&xHandle
		);
		return (xReturned == pdPASS);
	}
	return false;
}


/***
 * Internal function used by FreeRTOS to run the task
 * @param pvParameters
 */
void RGBLEDAgent::vTask( void * pvParameters )
{
    /* The parameter value is expected to be 1 as 1 is passed in the
    pvParameters value in the call to xTaskCreate() below.
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
    */
	RGBLEDAgent *task = (RGBLEDAgent *) pvParameters;
	task->run();
}

/***
 * Internal function to run the task from within the object
 */
void RGBLEDAgent::run(){
	uint8_t cmd[4];

	printf("Run\n");

	rgbPWM.setRGBb(0xFF,0xFF,0xFF);
	rgbPWM.setMode(RGBModeOff);
    for( ;; )
    {
    	if (uxQueueMessagesWaiting(xRGBQueue)> 0){
    		if( xQueueReceive( xRGBQueue,
				 cmd, ( TickType_t ) 10 ) == pdPASS ){
					rgbPWM.setRGBb(cmd[1], cmd[2], cmd[3]);
					rgbPWM.setMode((RGBMode)cmd[0]);
    		}
    	}
    	rgbPWM.tick();
		vTaskDelay(10);
    }
}

/***
 * Stop task
 * @return
 */
void RGBLEDAgent::stop(){
	if (xHandle != NULL){
		vTaskDelete(  xHandle );
		xHandle = NULL;
	}
}


/***
* Get high water for stack
* @return close to zero means overflow risk
*/
unsigned int RGBLEDAgent::getStakHighWater(){
	if (xHandle != NULL)
		return uxTaskGetStackHighWaterMark(xHandle);
	else
		return 0;
}
