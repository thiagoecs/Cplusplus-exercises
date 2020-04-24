/*
 * Lab2-1.cpp
 *
 *  Created on: Jan 24, 2020
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

	uint32_t sysTickRate;
	SystemCoreClockUpdate();
	Board_Init();
	Chip_Clock_SetSysTickClockDiv(1);
	sysTickRate = Chip_Clock_GetSysTickClockRate();
	SysTick_Config(sysTickRate / TICKRATE_HZ1);
	ITM_wrapper s;
	int count[3];
	int button;

	DigitalIoPin sw1(0,17,true, true, true);


	DigitalIoPin sw2(1,11,true, true, true);


	DigitalIoPin sw3(1,9,true, true, true);

	while (1){
		if(sw1.read()){
			count[0] = count[0] +10;
			}

		if(!sw1.read() && count[0]){
			button = 1;
			s.print(button,count[0]);
			count[0] = 0;
		}


		if(sw2.read()){
			count[1] = count[1] +10;
			}
		if(!sw2.read() && count[1]){
			button = 2;
			s.print(button, count[1]);
			count[1] = 0;
		}


		if(sw3.read()){

			count[2] = count[2] +10;
		}
		if(!sw3.read() && count[2]){
			button = 3;
			s.print(button, count[2]);
			count[2] = 0;
		}
		Sleep(10);
	}

}

