/*
 * DigitalIoPin2.cpp
 *
 *  Created on: Jan 22, 2020
 *      Author: thiag
 */

#include "DigitalIoPin.h"
#include "board.h"

DigitalIoPin::DigitalIoPin( const int port_, const int pin_, const bool input_, const bool pullup_, const bool invert_) :
port {port_}, pin {pin_}, input {input_}, pullup{pullup_}, invert{invert_}{
	LPC_IOCON->PIO[port][pin] = (1U + pullup) << 3 | 1U << 7 | invert << 6;

	if (input)
		LPC_GPIO->DIR[port] &= ~(1UL << pin);
	else
		LPC_GPIO->DIR[port] |= 1UL << pin;

}

bool DigitalIoPin::read(){
	return (bool) LPC_GPIO->B[port][pin];
}

void DigitalIoPin::write(bool value){
	if(invert)
		value = !value;
	LPC_GPIO->B[port][pin] = value;

}



