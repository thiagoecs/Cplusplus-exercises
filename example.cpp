#include "SimpleMenu.h"
#include "IntegerEdit.h"
#include "DigitalIoPin.h"
#include "Sleep.h"
#include "BarGraph.h"
#include "MenuItem.h"
#include "LiquidCrystal.h"

int main(void) {

Board_Startup();
    // TODO: insert code here
    Chip_RIT_Init(LPC_RITIMER);

	DigitalIoPin rs(0, 8, false, true, false);
	DigitalIoPin en(1, 6, false, true, false);
	DigitalIoPin d4(1, 8, false, true, false);
	DigitalIoPin d5(0, 5, false, true, false);
	DigitalIoPin d6(0, 6, false, true, false);
	DigitalIoPin d7(0, 7, false, true, false);
	LiquidCrystal *lcd = new LiquidCrystal(&rs, &en, &d4, &d5, &d6, &d7);

    lcd->begin(16,2);
    lcd->setCursor(0,0);

    SimpleMenu menu; /* this could also be allocated from the heap */
    IntegerEdit *temperature = new IntegerEdit(lcd, std::string("Temperature"));
    IntegerEdit *pressure = new IntegerEdit(lcd, std::string("Pressure"));
    IntegerEdit *humidity = new IntegerEdit(lcd, std::string("Humidity"));
    menu.addItem(new MenuItem(temperature));
    menu.addItem(new MenuItem(pressure));
    menu.addItem(new MenuItem(humidity));
    temperature->setValue(21);
    pressure->setValue(89);
    humidity->setValue(42);

    menu.event(MenuItem::show); // display first menu item
    /* simulate button presses */
    menu.event(MenuItem::up);
    menu.event(MenuItem::up);
    menu.event(MenuItem::up);
    menu.event(MenuItem::up);
    menu.event(MenuItem::ok);
    menu.event(MenuItem::up);
    menu.event(MenuItem::up);
    menu.event(MenuItem::ok);
    menu.event(MenuItem::down);
    menu.event(MenuItem::ok);
    menu.event(MenuItem::up);
    menu.event(MenuItem::back);
    menu.event(MenuItem::down);
    menu.event(MenuItem::up);
    menu.event(MenuItem::ok);
    menu.event(MenuItem::back);
    menu.event(MenuItem::up);
    menu.event(MenuItem::up);
    menu.event(MenuItem::up);

	while(1);
	
	return 0;
}
