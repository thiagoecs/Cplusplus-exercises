/*
 * Exercise01.cpp
 *
 *  Created on: Jan 15, 2020
 *      Author: thiag
 */
#define TICKRATE_HZ1 (1000)	/* 1000 ticks per second */
#include "board.h"
#include "ITM_write.h"
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
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 17, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN | IOCON_INV_EN));

	while (1) {
		if (Chip_GPIO_GetPinState(LPC_GPIO, 0, 17)){
			Board_LED_Toggle(0);
			Sleep(1000);
			Board_LED_Toggle(0);
			Board_LED_Toggle(1);
			Sleep(1000);
			Board_LED_Toggle(1);
			Board_LED_Toggle(2);
			Sleep(1000);
			Board_LED_Toggle(2);

		}

	}

	return 0;
}
