/*
 * BlinkPicoWTask.h
 *
 * Task to blink the Pico W onboard LED
 * Do not use with any other CY43 processes as not mutual protected
 *
 *  Created on: 30 Jul 2022
 *      Author: jondurrant
 */

#ifndef SRC_BLINKPICOWTASK_H_
#define SRC_BLINKPICOWTASK_H_

#include <FreeRTOS.h>
#include <task.h>
#include "pico/cyw43_arch.h"


#define BLINK_TIME 500

class BlinkPicoWTask {
public:
	/***
	 * Constructor
	 */
	BlinkPicoWTask();

	/***
	 * Destructor
	 */
	virtual ~BlinkPicoWTask();

	/***
	 *  create the task that will get picked up by scheduler
	 * @param priority - priority to run at
	 * */
	virtual  bool start(UBaseType_t priority = tskIDLE_PRIORITY);

	/***
	 * Stop task
	 * @return
	 */
	virtual void stop();


	/***
	 * Get high water for stack
	 * @return close to zero means overflow risk
	 */
	virtual unsigned int getStakHighWater();

	/***
	 * Get the FreeRTOS task being used
	 * @return
	 */
	virtual TaskHandle_t getTask();

protected:

	//The task
	TaskHandle_t xHandle = NULL;

private:
	/***
	 * Internal function to run up the task
	 * @param pvParameters
	 */
	static void vTask( void * pvParameters );

	/***
	 * Run loop for the task
	 */
	void run();
};

#endif /* SRC_BLINKPICOWTASK_H_ */
