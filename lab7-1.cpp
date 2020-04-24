


#include "SimpleMenu.h"
#include "IntegerEdit.h"
#include "Sleep.h"
#include "DigitalIoPin.h"
#include "BarGraph.h"
#include "LiquidCrystal.h"
#include "ITM_wrapper.h"

extern "C"{
void PIN_INT1_IRQHandler(void)
{
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(1));
	if (menu != nullptr){
		menu->event(MenuItem::up);
		counter2 = 0;
	}
}

void PIN_INT2_IRQHandler(void)
{
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(2));
	if (menu != nullptr){
		menu->event(MenuItem::ok);
		counter2 = 0;
	}
}

void PIN_INT3_IRQHandler(void)
{
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(3));
	if (menu != nullptr){
		menu->event(MenuItem::down);
		counter2 = 0;
	}
}
}

int main(void) {

 	Board_Startup();
	ITM_init();

	// TODO: insert code here
	Chip_RIT_Init(LPC_RITIMER);
	Chip_PININT_Init(LPC_GPIO_PIN_INT);


	DigitalIoPin sw1(0, 17, true, true, true);
	DigitalIoPin sw2(1, 11, true, true, true);
	DigitalIoPin sw3(1, 9, true, true, true);

	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_PININT);

	/* Reset the PININT block */
	Chip_SYSCTL_PeriphReset(RESET_PININT);

	/* Configure interrupt channel for the GPIO pin in INMUX block */
	Chip_INMUX_PinIntSel(1, 0, 17);
	Chip_INMUX_PinIntSel(2, 1, 11);
	Chip_INMUX_PinIntSel(3, 1, 9);

	/* Configure channel interrupt as edge sensitive and raising edge interrupt */
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(1));
	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH(1));
	Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH(1));

	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(2));
	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH(2));
	Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH(2));

	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(3));
	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH(3));
	Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH(3));

	/* Enable interrupt in the NVIC */
	NVIC_ClearPendingIRQ( PIN_INT1_IRQn);
	NVIC_EnableIRQ( PIN_INT1_IRQn);
	NVIC_ClearPendingIRQ( PIN_INT2_IRQn);
	NVIC_EnableIRQ(PIN_INT2_IRQn);
	NVIC_ClearPendingIRQ( PIN_INT3_IRQn);
	NVIC_EnableIRQ(PIN_INT3_IRQn);

	char str[80];


	DigitalIoPin rs(0, 8, false, true, false);
	DigitalIoPin en(1, 6, false);
	DigitalIoPin d4(1, 8, false);
	DigitalIoPin d5(0, 5, false);
	DigitalIoPin d6(0, 6, false);
	DigitalIoPin d7(0, 7, false);
	LiquidCrystal *lcd = new LiquidCrystal(&rs, &en, &d4, &d5, &d6, &d7);



	lcd->begin(16,2);
	lcd->setCursor(0,0);



	menu = new SimpleMenu; /* this could also be allocated from the heap */
	IntegerEdit *time = new IntegerEdit(lcd, std::string("Time"),10,0);
	IntegerEdit *blank = new IntegerEdit(lcd, std::string("Blank"),200,100);
	IntegerEdit *light = new IntegerEdit(lcd, std::string("Light"),2,0 );
	menu->addItem(new MenuItem(time));
	menu->addItem(new MenuItem(blank));
	menu->addItem(new MenuItem(light));





	while(1) {
		if (IntegerEdit::print_needed == true) {
			sprintf(str, "Time (0 – 10) :%d\n Blank (100 – 20): %d\n Light (0 – 2)= %d\n",time->getValue(), blank->getValue(), light->getValue());
			ITM_write(str);
			IntegerEdit::print_needed = false;
		}
	}
}
