/*
 * Lab3-1.cpp
 *
 *  Created on: Jan 29, 2020
 *      Author: thiag
 */


#define TICKRATE_HZ1 (1000)	/* 1000 ticks per second */
#include "board.h"
#include "chip.h"
#include "ITM_write.h"
#include "DigitalIoPin.h"
#include "ITM_wrapper.h"
#include <cstdio>
#include <atomic>
#include <ctype.h>
static volatile std::atomic_int counter;
#ifdef __cplusplus
extern "C" {
#endif



void SysTick_Handler(void)
{
	if(counter > 0)
		counter--;
}
#ifdef __cplusplus
}
#endif
void Sleep(int ms)
{
	counter = ms;
	while(counter > 0) {
		__WFI();
	}
}

int main(void)
{
#if defined (__USE_LPCOPEN)
	// Read clock settings and update SystemCoreClock variable
	SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
	// Set up and initialize all required blocks and
	// functions related to the board hardware
	Board_Init();
	// Set the LED to the state of "On"
	Board_LED_Set(0, true);
#endif
#endif
	Board_UARTPutSTR("\r\nHello, World\r\n");
	Board_UARTPutChar('!');
	Board_UARTPutChar('\r');
	Board_UARTPutChar('\n');
	int c;
	bool value = true;
	DigitalIoPin sw1(0,17,true, true, true);
	DigitalIoPin red(0,25,false, true, true);
	while(1) { // echo back what we receive
		c = Board_UARTGetChar();
		if(c != EOF) {
			if(c == '\n') Board_UARTPutChar('\r'); // precede linefeed with carriage return
			//Board_UARTPutChar(c);
			if (red.read()){
				Board_UARTPutChar(toupper(c));
			}
			else if(!red.read()){
				Board_UARTPutChar(tolower(c));
				if(c == '\r') Board_UARTPutChar('\n'); // send line feed after carriage return
			}
		}

		/*if(sw1.read() && red.read()){
			red.write(false);
		}
		if(sw1.read() && !red.read()){
			red.write(true);
		}*/
			if(sw1.read()){
				red.write((red.read()));
			}

		/*if (red.read() && isalpha(c)){
				Board_UARTPutChar(toupper(c));
			}
			else if(!red.read() && isalpha(c)){
				Board_UARTPutChar(tolower(c));
			}
		 */
		//Board_UARTPutChar(c);
	}


	return 0;
}
