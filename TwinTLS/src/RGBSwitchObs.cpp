/*
 * RGBSwitchObs.cpp
 *
 * Switch Observer that will cycle the IOT Device state through colour of a rainbow
 *
 *  Created on: 8 Aug 2022
 *      Author: jondurrant
 */

#include "RGBSwitchObs.h"

/***
 * Constructor
 * @param state - State object to interface too
 */
RGBSwitchObs::RGBSwitchObs(StateExample *state) {
	pState = state;

}

/***
 * Destructor
 */
RGBSwitchObs::~RGBSwitchObs() {
	// NOP
}



/***
 * Handle a short press from the switch
 * @param gp - GPIO number of the switch
 */
void RGBSwitchObs::handleShortPress(uint8_t gp){

	if (xSeq > xRainbowCount){
		xSeq = 0;
	}

	if (xSeq == 0){
		pState->setOn(true);
	}

	if (xSeq == xRainbowCount){
		pState->setOn(false);
	} else {
		pState->setRGB(pRainbow[xSeq]);
	}

	xSeq++;

}

/***
 * Handle a short press from the switch
 * @param gp - GPIO number of the switch
 */
void RGBSwitchObs::handleLongPress(uint8_t gp){
	handleShortPress(gp);

}
