/*
 * Exercise03.cpp
 *
 *  Created on: Jan 22, 2020
 *      Author: thiag
 */
#define TICKRATE_HZ1 (1000)
#include "Dice.h"
#include "DigitalIoPin.h"
#include "board.h"
#include <atomic>
#include <cstdlib>
#include "Sleep.h"

int main(){
	Board_Startup();

	int counter=0;

	DigitalIoPin test(0,8,true, true, true);
	DigitalIoPin operate(1,6,true, true, true);
	Dice dice;

	while (1) {

		if(test.read()){
			dice.Show(7);
			if(!test.read()){
				dice.Show(0);
			}
		}
		else if (operate.read()){
			dice.Show(0);
			while(operate.read());
			dice.Show((rand()%6) + 1);

			}
		}


}
