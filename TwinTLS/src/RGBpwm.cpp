/*
 * RGBpwm.cpp
 *
 * RGB LED driver for a common cathode LED
 *
 *  Created on: 24 Oct 2021
 *      Author: jondurrant
 */

#include "RGBpwm.h"
#include <hardware/pwm.h>
#include <string.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"


#define SLOWTICK  800/10
#define FASTTICK  200/10
#define RGBTICK  2000/10



/***
* Destructor
* */
RGBpwm::~RGBpwm() {
	// NOP
}

/***
 * Default constructor, setup must be run on object
 */
RGBpwm::RGBpwm(){
	//NOP
}

/***
 * Set up RGB pwm for the defined GPIO Pins
 * @param redPin - GPIO number
 * @param greenPin - GPIO number
 * @param bluePin - GPIO number
 */
RGBpwm::RGBpwm(uint8_t redPin, uint8_t greenPin, uint8_t bluePin){
	setup(redPin, greenPin, bluePin);
}

/***
 * Setup GPIO pins connected to the RGB Led
 * @param redPin
 * @param greenPin
 * @param bluePin
 */
void RGBpwm::setup(uint8_t redPin, uint8_t greenPin, uint8_t bluePin){
	this->xRedPin = redPin;
	this->xGreenPin = greenPin;
	this->xBluePin = bluePin;

	gpio_init(xRedPin);
	gpio_set_function(xRedPin, GPIO_FUNC_PWM);
	pwm_set_gpio_level(xRedPin, 0);
	uint slice_num = pwm_gpio_to_slice_num(xRedPin);
	pwm_set_enabled(slice_num, true);

	gpio_init(xGreenPin);
	gpio_set_function(xGreenPin, GPIO_FUNC_PWM);
	pwm_set_gpio_level(xGreenPin, 0);
	slice_num = pwm_gpio_to_slice_num(xGreenPin);
	pwm_set_enabled(slice_num, true);

	gpio_init(xBluePin);
	gpio_set_function(xBluePin, GPIO_FUNC_PWM);
	pwm_set_gpio_level(xBluePin, 0);
	slice_num = pwm_gpio_to_slice_num(xBluePin);
	pwm_set_enabled(slice_num, true);

}

/***
 * Set RGB colour of the LED. Max brightness is 0xffff
 * @param rgb - array is copied
 */
void RGBpwm::setRGB(uint16_t rgb[3]){
	setRGB(rgb[0], rgb[1], rgb[2]);
}

/***
 * Set RGB colour of LED, based on 16 bit integers
 * @param r
 * @param g
 * @param b
 */
void RGBpwm::setRGB(uint16_t r, uint16_t g, uint16_t b){
	memcpy(pPrevRgb, pRgb, sizeof(pRgb));
	pRgb[0] = r;
	pRgb[1] = g;
	pRgb[2] = b;

	xChanged = true;
}

/***
 * Set RGB based on 8 bit brightness, internally squares input
 * @param r
 * @param g
 * @param b
 */
void RGBpwm::setRGBb(uint8_t r, uint8_t g, uint8_t b){
	uint16_t red = r * r;
	uint16_t green = g * g;
	uint16_t blue = b * b;
	setRGB(red, green, blue);
}

/***
 * Set mode: On, Off, Flash, etc
 * @param m
 */
void RGBpwm::setMode(RGBMode m){
	xPrevMode = xMode;
	xMode = m;
	xChanged = true;
}

/***
 * tick function called by agent on each loop to update the led.
 */
void RGBpwm::tick(){
	//printf("Tick %d\n", xTickCount);


	xTickCount = xTickCount + 1;

	if (xMode == RGBModeOnce){
		off();
		vTaskDelay(FASTTICK/2);
		on();
		vTaskDelay(FASTTICK/2);
		off();
		vTaskDelay(FASTTICK/2);
		setMode(xPrevMode);
		setRGB(pPrevRgb);
	}

	if (xChanged){
		xChanged = false;
		switch(xMode){
		case RGBModeOff:
			off();
			break;
		case RGBModeOn:
			on();
			break;
		case RGBModeFast:
			xTickCount = 0;
			xState = true;
			on();
			break;
		case RGBModeSlow:
			xTickCount = 0;
			xState = true;
			on();
			break;
		}
	}

	switch(xMode){
	case RGBModeFast:
		if (xTickCount >= FASTTICK){
			xTickCount = 0;
			if (xState == true){
				on();
				xState = false;
			} else {
				off();
				xState = true;
			}
		}
		break;
	case RGBModeSlow:
		if (xTickCount >= SLOWTICK){
			xTickCount = 0;
			if (xState){
				on();
				xState = false;
			} else {
				off();
				xState = true;
			}
		}
		break;
	default:
		xTickCount = 0;
		break;
	}
}

/***
 * Turn LED Off
 */
void RGBpwm::off(){
	pwm_set_gpio_level(xRedPin, 0);
	pwm_set_gpio_level(xGreenPin, 0);
	pwm_set_gpio_level(xBluePin, 0);
}

/***
 * Turn desired LED colour on
 */
void RGBpwm::on(){
	pwm_set_gpio_level(xRedPin, pRgb[0]);
	pwm_set_gpio_level(xGreenPin, pRgb[1]);
	pwm_set_gpio_level(xBluePin, pRgb[2]);
}



