/*
 * LAb5-1.cpp
 *
 *  Created on: Feb 7, 2020
 *      Author: thiag
 */


#include"board.h"
#include "DigitalIoPin.h"
#include "MorseSender.h"
#include <atomic>
#include <stdio.h>
#include <ctype.h>
#include "Sleep.h"
#include "ritimer_15xx.h"
#include "LiquidCrystal.h"


/*void delayMicroseconds(unsigned int us)
{
	uint64_t compval = (uint64_t) SystemCoreClock * us / 1000000;
	Chip_RIT_Disable(LPC_RITIMER);
	Chip_RIT_SetCompareValue(LPC_RITIMER, compval);
	Chip_RIT_SetCounter(LPC_RITIMER, 0);
	Chip_RIT_Enable(LPC_RITIMER);
	while(!Chip_RIT_GetIntStatus(LPC_RITIMER));
	Chip_RIT_Disable(LPC_RITIMER);
	Chip_RIT_ClearIntStatus(LPC_RITIMER);
}
*/


int main(void)
{
	Board_Startup();
	char buffer[33];
	const char status [2][5] {"DOWN", "UP"};
	Chip_RIT_Init(LPC_RITIMER); // initialize RIT (enable clocking etc.)
	DigitalIoPin rs(0, 8, false, true, false);
	DigitalIoPin en(1, 6, false, true, false);
	DigitalIoPin d4(1, 8, false, true, false);
	DigitalIoPin d5(0, 5, false, true, false);
	DigitalIoPin d6(0, 6, false, true, false);
	DigitalIoPin d7(0, 7, false, true, false);
	DigitalIoPin B1(0,17,true, true, true);
	DigitalIoPin B2(1,11,true, true, true);
	DigitalIoPin B3(1,9,true, true, true);

	LiquidCrystal lcd(&rs, &en, &d4, &d5, &d6, &d7);
	// configure display geometry
	lcd.begin(16, 2);
	// set the cursor to column 0, line 1
	// (note: line 1 is the second row, since counting begins with 0):
	//lcd.setCursor(0, 1);
	// Print a message to the LCD.
	//lcd.write('A');

	lcd.setCursor(0,0);
	sprintf(buffer, "%-6s%-6s%-4s", "B1", "B2", "B3");
	lcd.print(buffer);

	while(1){
		sprintf(buffer +16,"%-6s%-6s%-4s", status[B1.read()], status[B2.read()], status[B3.read()]);
		lcd.setCursor(0,1);
		lcd.print(buffer + 16);
		Sleep(100);
	}

	/*while(1){
		rs.write(true);
		delayMicroseconds(55);
		rs.write(false);
		delayMicroseconds(35);
		rs.write(true);
		delayMicroseconds(40);
		rs.write(false);
		delayMicroseconds(20);

	}
	*/

}
