#include"board.h"
#include "DigitalIoPin.h"
#include "MorseSender.h"
#include <atomic>
#include <stdio.h>
#include <ctype.h>
#include "Sleep.h"

int main(void)
{
	Board_Startup();

	int c, i;
	char buffer[100];
	DigitalIoPin decoder(0, 8, false, true, false);
	DigitalIoPin led(0, 25, false,true,true);

	MorseSender code(&led, &decoder);

	while(1) { // echo back what we receive
		while(i < 80 && c != '\n') {
			c = Board_UARTGetChar();
			if(c != EOF) {
				if(c == '\n')
					Board_UARTPutChar('\r'); // precede linefeed with carriage return

				Board_UARTPutChar(c);

				if(c == '\r') {
					Board_UARTPutChar('\n');
					c = '\n';
				}
				else {
					buffer[i] = (char) toupper(c);
				}
				buffer[++i] = '\0';
			}
		}

		code.converter(buffer);
		i = c = 0;
	}




return 0;
}
