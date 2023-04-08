/*
 * RGBSwitchObs.h
 *
 * Switch Observer that will cycle the IOT Device state through colour of a rainbow
 *
 *  Created on: 8 Aug 2022
 *      Author: jondurrant
 */

#ifndef SRC_RGBSWITCHOBS_H_
#define SRC_RGBSWITCHOBS_H_

#include "SwitchObserver.h"
#include "StateExample.h"

class RGBSwitchObs : public SwitchObserver {
public:
	/***
	 * Constructor
	 * @param state - State object to interface too
	 */
	RGBSwitchObs(StateExample *state);

	/***
	 * Destructor
	 */
	virtual ~RGBSwitchObs();

	/***
	 * Handle a short press from the switch
	 * @param gp - GPIO number of the switch
	 */
	virtual void handleShortPress(uint8_t gp);

	/***
	 * Handle a short press from the switch
	 * @param gp - GPIO number of the switch
	 */
	virtual void handleLongPress(uint8_t gp);

private:

	//State object
	StateExample *pState = NULL;

	//Sequence within the rainbox
	uint8_t xSeq =0;

	//Rainbow count
	const uint8_t xRainbowCount = 7;

	//Rainbow sequence as Red, Green, Blue tuples
	uint8_t pRainbow[7][3]= {
		{0x94, 0x00, 0xD3},
		{0x4B, 0x00, 0x82},
		{0x00, 0x00, 0xFF},
		{0x00, 0xFF, 0x00},
		{0xFF, 0xFF, 0x00},
		{0xFF, 0x7F, 0x00},
		{0xFF, 0x00, 0x00}
	};
};

#endif /* SRC_RGBSWITCHOBS_H_ */
