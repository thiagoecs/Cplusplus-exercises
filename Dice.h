/*
 * Dice.h
 *
 *  Created on: Jan 22, 2020
 *      Author: thiag
 */

#ifndef DICE_H_
#define DICE_H_
#include "DigitalIoPin.h"
#include "board.h"

class Dice {
public:
	Dice();
	virtual ~Dice();
	void Show(int number);
private:
	 DigitalIoPin leds[7];
	 //const bool state, mode;

};



#endif /* DICE_H_ */
