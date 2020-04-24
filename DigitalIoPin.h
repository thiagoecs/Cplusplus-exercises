/*
 * DigitalIoPin2.h
 *
 *  Created on: Jan 22, 2020
 *      Author: melinda
 */
#include "board.h"
#ifndef DIGITALIOPIN_H_
#define DIGITALIOPIN_H_

class DigitalIoPin {
public:
	DigitalIoPin(const int port_ = 0, const int pin_ = 0, const bool input_ = true, const bool pullup_ = true, const bool invert_ = false);
	virtual ~DigitalIoPin() {};
	bool read();
	void write(bool value);
private:
	const int port,pin;
	const bool input, pullup,invert;

};

#endif /* DIGITALIOPIN_H_ */
