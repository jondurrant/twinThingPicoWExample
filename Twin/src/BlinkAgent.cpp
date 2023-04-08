/*
 * BlinkAgent.cpp
 * Blink an external LED as a task
 *
 *  Created on: 7-Aug-2022
 *      Author: jondurrant
 */

#include "FreeRTOS.h"
#include "task.h"
#include "BlinkAgent.h"
#include <cstring>


/***
* Constructor
* €param name - task name
* @param gp - GP Pad number for LED
* @param delay - delay in microseconds
*/
BlinkAgent::BlinkAgent(const char *name, uint8_t gp,unsigned int delay) {
	strcpy(pName, name);
	xGP = gp;
	xDelay = delay;
	gpio_init(xGP);
	gpio_set_dir(xGP, GPIO_OUT);
}

/***
 * Destructor
 */
BlinkAgent::~BlinkAgent() {
	//NOP
}

/***
 *  create the vtask, will get picked up by scheduler
 *
 **/
bool BlinkAgent::start(UBaseType_t priority){
	BaseType_t res;
	res = xTaskCreate(
		BlinkAgent::vTask,       /* Function that implements the task. */
		pName,   /* Text name for the task. */
		40,             /* Stack size in words, not bytes. */
		( void * ) this,    /* Parameter passed into the task. */
		priority,/* Priority at which the task is created. */
		&xHandle
	);
	return (res == pdPASS);
}



/***
 * Internal function used by FreeRTOS to run the task
 * @param pvParameters
 */
 void BlinkAgent::vTask( void * pvParameters ){
	 BlinkAgent *task = (BlinkAgent *) pvParameters;
	 if (task != NULL){
		 task->run();
	 }
 }

 /***
  * Main Run Task for agent
  */
 void BlinkAgent::run(){

	for( ;; ){
		gpio_put(xGP, 1);
		vTaskDelay(xDelay);
		gpio_put(xGP, 0);
		vTaskDelay(xDelay);
	}

 }

/***
 * Stop task
 * @return
 */
void BlinkAgent::stop(){
	if (xHandle != NULL){
		vTaskDelete(  xHandle );
		xHandle = NULL;
	}
}

/***
 * Get high water for stack
 * @return close to zero means overflow risk
 */
unsigned int BlinkAgent::getStakHighWater(){
	if (xHandle != NULL)
		return uxTaskGetStackHighWaterMark(xHandle);
	else
		return 0;
}



