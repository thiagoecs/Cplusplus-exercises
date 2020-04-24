/*
 * Exercise02.cpp
 *
 *  Created on: Jan 15, 2020
 *      Author: thiag
 */
#define TICKRATE_HZ1 (1000)	/* 1000 ticks per second */
#include "board.h"
#include "chip.h"
#include <atomic>
#include "DigitalIoPin.h"
static volatile std::atomic_int counter;
#ifdef __cplusplus
extern "C" {
#endif

void SysTick_Handler(void)
{
	if(counter > 0) counter--;
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


int main (){
	uint32_t sysTickRate;

	SystemCoreClockUpdate();
	Board_Init();
	Chip_Clock_SetSysTickClockDiv(1);
	sysTickRate = Chip_Clock_GetSysTickClockRate();
	SysTick_Config(sysTickRate / TICKRATE_HZ1);

	unsigned int count1 = 0, count2 = 0, count3 = 0;
	DigitalIoPin sw1(0,17,true, true, true);


	DigitalIoPin sw2(1,11,true, true, true);


	DigitalIoPin sw3(1,9,true, true, true);


	while (1) {

		if(sw1.read() && !Board_LED_Test(0)){
			Board_LED_Toggle(0);
			count1 = 0;
		}
		else if(!sw1.read() && Board_LED_Test(0)){
			count1 = count1 + 1;
			if (count1 == 100){
				Board_LED_Toggle(0);
			}
		}
		if(sw2.read() && !Board_LED_Test(1)){
			Board_LED_Toggle(1);
			count2 = 0;
		}
		else if(!sw2.read() && Board_LED_Test(1)){
			count2 = count2 + 1;
			if (count2 == 100){
				Board_LED_Toggle(1);
			}
		}
		if(sw3.read() && !Board_LED_Test(2)){
			Board_LED_Toggle(2);
			count3 = 0;
		}
		else if(!sw3.read() && Board_LED_Test(2)){
			count3 = count3 + 1;
			if (count3 == 100){
				Board_LED_Toggle(2);
			}
		}

		Sleep(10);

	}

	return 0;
}
