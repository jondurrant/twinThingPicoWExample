/*
 * RGBpwm.h
 *
 * RGB LED driver for a common cathode LED
 *
 *  Created on: 24 Oct 2021
 *      Author: jondurrant
 */

#ifndef RGBPWM_H_
#define RGBPWM_H_

#include "pico/stdlib.h"

/***
 * Modes for the RGB LED
 */
enum RGBMode { RGBModeOff, RGBModeOn, RGBModeSlow, RGBModeFast, RGBModeOnce };

class RGBpwm {
public:

	/***
	 * Default constructor, setup must be run on object
	 */
	RGBpwm();

	/***
	 * Set up RGB pwm for the defined GPIO Pins
	 * @param redPin - GPIO number
	 * @param greenPin - GPIO number
	 * @param bluePin - GPIO number
	 */
	RGBpwm(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);

	/***
	 * Destructor
	 */
	virtual ~RGBpwm();

	/***
	 * Setup GPIO pins connected to the RGB Led
	 * @param redPin
	 * @param greenPin
	 * @param bluePin
	 */
	void setup(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);

	/***
	 * Set RGB colour of the LED. Max brightness is 0xffff
	 * @param rgb - array is copied
	 */
	void setRGB(uint16_t rgb[3]);

	/***
	 * Set RGB colour of LED, based on 16 bit integers
	 * @param r
	 * @param g
	 * @param b
	 */
	void setRGB(uint16_t r, uint16_t g, uint16_t b);

	/***
	 * Set RGB based on 8 bit brightness, internally squares input
	 * @param r
	 * @param g
	 * @param b
	 */
	void setRGBb(uint8_t r, uint8_t g, uint8_t b);

	/***
	 * Set mode: On, Off, Flash, etc
	 * @param m
	 */
	void setMode(RGBMode m);

	/***
	 * tick function called by agent on each loop to update the led.
	 */
	void tick();

private:
	uint8_t xRedPin;
	uint8_t xGreenPin;
	uint8_t xBluePin;

	uint16_t pRgb[3];
	uint16_t pPrevRgb[3]
					 ;
	bool xChanged = false;
	RGBMode xMode = RGBModeOff;
	RGBMode xPrevMode = RGBModeOff;
	unsigned int xTickCount = 0;
	bool xState = false;

	/***
	 * Turn LED Off
	 */
	void off();

	/***
	 * Turn LED on to specifed colour
	 */
	void on();

};

#endif /* RGBPWM_H_ */
