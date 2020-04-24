#include "Sleep.h"
#include"MenuItem.h"

std::atomic_int counter, counter2, blink_period;
DigitalIoPin *BlinkingLED = nullptr;
SimpleMenu *menu = nullptr;

/*extern "C" { void SysTick_Handler(void) {

	if (counter > 0) counter--;

	if(++tick >= blink_period){
		BlinkingLED->write(!BlinkingLED->read());
		tick =0;
	}
};
}*/
//

extern "C" { void SysTick_Handler(void) {
	if(counter > 0)
		--counter;

	/*if (++counter2 > 10000){
		menu->event(MenuItem::back);
		counter2 = 0;
	}
*/

};
}
void Sleep(int ms) {
	counter = ms;
	while(counter > 0) {
		__WFI();
	}
}

void Board_Startup() {
	uint32_t sysTickRate;
	SystemCoreClockUpdate();
	Board_Init();
	Chip_Clock_SetSysTickClockDiv(1);
	sysTickRate = Chip_Clock_GetSysTickClockRate();
	SysTick_Config(sysTickRate / 1000);
}
