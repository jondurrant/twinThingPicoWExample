/*
 * StateExample.h
 *
 * RGB light switch example
 *
 *  Created on: 19 Sept 2021
 *      Author: jondurrant
 */

#ifndef STATEEXAM_H_
#define STATEEXAM_H_



#include "StateTemp.h"
#include <stdbool.h>
#include "pico/stdlib.h"

/***
 * State include temperate, uptime, RGB colour and On status
 */
class StateExample: public StateTemp {
public:
	StateExample();
	virtual ~StateExample();
	StateExample(const StateExample &other);

	/***
	 * Get RGB as an array
	 * @return unsigned char[]
	 */
	const unsigned char* getRGB() const;

	/***
	 * Sets RGB based on array provided.
	 * Copies array so no need to allocate parameter
	 * @param newRGB - unsigned char[3]
	 */
	void setRGB(unsigned char* newRGB);

	/***
	 * Sets RGB based on three parameters
	 * @param r
	 * @param g
	 * @param b
	 */
	void setRGB(unsigned char r, unsigned char g, unsigned char b);

	/***
	 * Gets the On status of the light
	 * @return
	 */
	bool getOn() const;

	/***
	 * Sets the on status of the light
	 * @param b
	 */
	void setOn(bool b);

	/***
	 * Update state data from a json structure
	 * @param json
	 */
	virtual void updateFromJson(json_t const *json);

	/***
	 * Retrieve state of object in JSON format
	 * @param buf - buffer to write to
	 * @param len - length of buffer
	 * @return length of json or zero if we ran out of space
	 */
	virtual unsigned int state(char *buf, unsigned int len) ;


protected:
	/***
	 * Retrieve RGB in json format
	 * @param buf
	 * @param len
	 * @return
	 */
	char* jsonRGB(char *buf, unsigned int len);

	/***
	 * Retried On status in JSON format
	 * @param buf
	 * @param len
	 * @return
	 */
	char* jsonOn(char *buf, unsigned int len);

private:
	//Light colour in RGB format, one bite per element
	unsigned char rgb[3] = {0, 0, 0};
	//Is light on
	bool on = false;

};

#endif /* STATETEMP_H_ */
