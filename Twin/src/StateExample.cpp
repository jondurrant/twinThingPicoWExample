/*
 * StateExample.cpp
 *
 * Simulates an RGB  light
 *
 *  Created on: 19 Sept 2021
 *      Author: jondurrant
 */

#include "StateExample.h"
#include "hardware/adc.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "json-maker/json-maker.h"

#define RGBSLOT 3
#define ONSLOT  4

/***
 * State will have 4 element two from StateTemperature and two added here
 */
StateExample::StateExample() {
	elements=5;

	jsonHelpers[RGBSLOT] = (StateFunc)&StateExample::jsonRGB;
	jsonHelpers[ONSLOT] = (StateFunc)&StateExample::jsonOn;

}

/***
 * Destructor
 */
StateExample::~StateExample() {
	// TODO Auto-generated destructor stub
}

/***
 * Copy constructor
 * @param other
 */
StateExample::StateExample(const StateExample &other):
	StateTemp(other){

	on = other.getOn();
	memcpy(rgb, other.getRGB(), 3);
}

/***
 * Set On status of switch
 * @param bool
 */
void StateExample::setOn(bool b){
	on = b;
	setDirty(ONSLOT);
}

/***
 * Get on status of switch
 * @return
 */
bool StateExample::getOn() const{
	return on;
}

/***
 * get RGB status as array of uint8_ts
 * @return uint8_t[3]
 */
const uint8_t* StateExample::getRGB() const{
	return rgb;
}

/***
 * sets the RGB based on an array of RGN value
 * @param newRGB uint8_t [r, g, b]
 */
void StateExample::setRGB(uint8_t* newRGB){
	memcpy(rgb, newRGB, 3);
	setDirty(RGBSLOT);
}

/***
 * Sets RGB based on three parameters
 * @param r
 * @param g
 * @param b
 */
void StateExample::setRGB(uint8_t r, uint8_t g, uint8_t b){
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
	setDirty(RGBSLOT);
}

/***
 * Retrieve on status in JSON format
 * @param buf
 * @param len
 * @return
 */
char* StateExample::jsonOn(char *buf, unsigned int len){
	char *p = buf;
    p = json_bool( p, "on", getOn(), &len);
    return p;
}

/***
 * Retrieve RGB valueu in JSON format
 * @param buf
 * @param len
 * @return
 */
char* StateExample::jsonRGB(char *buf, unsigned int len){
	char *p = buf;
    p = json_arrOpen( p, "rgb", &len);
    for (uint8_t i=0; i < 3; i++){
    	p = json_uint( p, NULL, getRGB()[i], &len );
    }
    p = json_arrClose( p, &len);
    return p;
}

/***
* Update state data from a json structure
* @param json
*/
void StateExample::updateFromJson(json_t const *json){
	StateTemp::updateFromJson(json);

	json_t const *jp;
	uint8_t newRGB[3]={0, 0, 0};
	bool rgbOK = true;

	jp = json_getProperty(json, "on");
	if (jp){
		if (JSON_BOOLEAN == json_getType(jp)){
			bool b = json_getBoolean(jp);
			setOn(b);
		}
	}

	jp = json_getProperty(json, "rgb");
	if (jp){
		if (JSON_ARRAY == json_getType(jp)){
			jp = json_getChild(jp);
			for (uint8_t i=0; i < 3; i++){
				if (jp){
					if (JSON_INTEGER == json_getType(jp)){
						int col = json_getInteger(jp);
						if ((col >= 0) && (col <= 0xFF)){
							newRGB[i] = (uint8_t) col;
						} else {
							rgbOK = false;
						}
					}
					else {
						rgbOK = false;
					}
				} else {
					rgbOK = false;
				}
				jp = json_getSibling(jp);
			}
			if (rgbOK){
				setRGB(newRGB);
			}
		}
	}

}

/***
 * Retrieve state of object in JSON format
 * @param buf - buffer to write to
 * @param len - length of buffer
 * @return length of json or zero if we ran out of space
 */
unsigned int StateExample::state(char *buf, unsigned int len){
	updateTemp();
	return StateTemp::state(buf, len);
}
