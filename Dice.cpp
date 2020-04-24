/*
 * Dice.cpp
 *
 *  Created on: Jan 22, 2020
 *      Author: thiag
 */

#include "Dice.h"

Dice::Dice(): leds{{1,9,false}, {0,29,false},{0,9,false},{0,10,false},{0,16,false},{1,3,false},{0,0,false}} {}

// TODO Auto-generated constructor stub



Dice::~Dice() {
	// TODO Auto-generated destructor stub
}

void Dice::Show(int number){
	switch(number){
	case 0:
		for(auto& led : leds){
			led.write(false);
		};
		break;
	case 1:
		for(auto& led : leds){
			led.write(false);
		};
		leds[3].write(true);
		break;
	case 2:
		for(auto& led : leds){
			led.write(false);
		};
		leds[2].write(true);
		leds[6].write(true);
		break;
	case 3:
		for(auto& led : leds){
			led.write(false);
		};
		leds[2].write(true);
		leds[3].write(true);
		leds[6].write(true);
		break;
	case 4:
		for(auto& led : leds){
			led.write(false);
		};
		leds[0].write(true);
		leds[2].write(true);
		leds[4].write(true);
		leds[6].write(true);
		break;
	case 5:
		for(auto& led : leds){
			led.write(false);
		};
		leds[0].write(true);
		leds[2].write(true);
		leds[3].write(true);
		leds[4].write(true);
		leds[6].write(true);
		break;
	case 6:
		for(auto& led : leds){
			led.write(false);
		};
		leds[0].write(true);
		leds[1].write(true);
		leds[2].write(true);
		leds[4].write(true);
		leds[5].write(true);
		leds[6].write(true);
		break;
	default:
		for(auto& led : leds){
			led.write(true);
		};
		break;


	}
}

