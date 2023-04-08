/*
 * BlinkPicoWTask.cpp
 *
 *  Created on: 30 Jul 2022
 *      Author: jondurrant
 */

#include "BlinkPicoWTask.h"

/***
 * Constructor
 */
BlinkPicoWTask::BlinkPicoWTask() {
	// NOP

}

/***
 * Destructor
 */
BlinkPicoWTask::~BlinkPicoWTask() {
	stop();
}

/***
 * Stop task
 * @return
 */
void BlinkPicoWTask::stop(){
	if (xHandle != NULL){
		vTaskDelete(  xHandle );
		xHandle = NULL;
	}
}


/***
* Get high water for stack
* @return close to zero means overflow risk
*/
unsigned int BlinkPicoWTask::getStakHighWater(){
	if (xHandle != NULL)
		return uxTaskGetStackHighWaterMark(xHandle);
	else
		return 0;
}


/***
* Get the FreeRTOS task being used
* @return
*/
TaskHandle_t BlinkPicoWTask::getTask(){
	return xHandle;
}

/***
 *  create the task that will get picked up by scheduler
 *
 * */
bool BlinkPicoWTask::start(UBaseType_t priority){
	BaseType_t res;
	res = xTaskCreate(
			BlinkPicoWTask::vTask,       /* Function that implements the task. */
		"Blink",   /* Text name for the task. */
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
 void BlinkPicoWTask::vTask( void * pvParameters ){
	 BlinkPicoWTask *task = (BlinkPicoWTask *) pvParameters;
	 if (task != NULL){
		 task->run();
	 }
 }

 /***
  * Main Run Task for agent
  */
 void BlinkPicoWTask::run(){

	printf("Blink Started\n");

	for( ;; )
	{
		cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
		vTaskDelay(BLINK_TIME);
		cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
		vTaskDelay(BLINK_TIME);
	}

 }
