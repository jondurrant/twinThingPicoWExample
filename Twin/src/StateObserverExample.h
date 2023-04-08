/*
 * StateObserverExample.h
 *
 * Observer state and link it to the state of an RGB LED
 *
 *  Created on: 8 Aug 2022
 *      Author: jondurrant
 */

#ifndef SRC_STATEOBSERVEREXAMPLE_H_
#define SRC_STATEOBSERVEREXAMPLE_H_

#include <StateObserver.h>
#include "RGBLEDAgent.h"
#include "StateExample.h"

class StateObserverExample : public StateObserver {
public:
	/***
	 * Constructor
	 * @param agent - RGB LED to manage
	 * @param state - State to take changes from
	 */
	StateObserverExample(RGBLEDAgent *agent, StateExample *state);

	/***
	 * Destructor
	 */
	virtual ~StateObserverExample();

	/***
	 * Notification of a change of a state item with the State object.
	 * @param dirtyCode - Representation of item changed within state. Used to pull back delta
	 */
	virtual void notifyState(uint16_t dirtyCode);

private:
	//RGB LED Agent
	RGBLEDAgent *pAgent = NULL;

	//State object
	StateExample *pState = NULL;
};

#endif /* SRC_STATEOBSERVEREXAMPLE_H_ */
