#include "board.h"
#include "chip.h"
#include <atomic>
#include <cstdio>
#include "DigitalIoPin.h"
#include "Sleep.h"
#include "LiquidCrystal.h"
#include "ITM_wrapper.h"
#include "i2cm.h"
#include "BarGraph.h"




/* Start ADC calibration */
void ADC_StartCalibration(LPC_ADC_T *pADC)
{
	// clock divider is the lowest 8 bits of the control register
	/* Setup ADC for about 500KHz (per UM) */
	uint32_t ctl = (Chip_Clock_GetSystemClockRate() / 500000) - 1;
	/* Set calibration mode */
	ctl |= ADC_CR_CALMODEBIT;
	pADC->CTRL = ctl;
	/* Calibration is only complete when ADC_CR_CALMODEBIT bit has cleared */
	while(pADC->CTRL & ADC_CR_CALMODEBIT) { };
}
int main(void) {
#if defined (__USE_LPCOPEN)
	// Read clock settings and update SystemCoreClock variable
	SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
	// Set up and initialize all required blocks and
	// functions related to the board hardware
	Board_Init();
	ITM_init();
	Init_I2C_PinMux();
	setupI2CMaster();
	Chip_RIT_Init(LPC_RITIMER);
	// Set the LED to the state of "On"
	Board_LED_Set(0, true);

	DigitalIoPin rs(0, 8, false, true, false);
	DigitalIoPin en(1, 6, false, true, false);
	DigitalIoPin d4(1, 8, false, true, false);
	DigitalIoPin d5(0, 5, false, true, false);
	DigitalIoPin d6(0, 6, false, true, false);
	DigitalIoPin d7(0, 7, false, true, false);
	DigitalIoPin red(0, 25, false, true, true);
	DigitalIoPin green(0, 3, false, true, true);
	DigitalIoPin blue(1, 1, false, true, true);
	LiquidCrystal lcd(&rs, &en, &d4, &d5, &d6, &d7);
	lcd.begin(16, 2);
	lcd.setCursor(0,0);

	BarGraph bargraph(&lcd, 50);

	unsigned char TC74RegisterData[2] = {0};

#endif
#endif
	// TODO: insert code here
	/* Setup ADC for 12-bit mode and normal power */
	Chip_ADC_Init(LPC_ADC0, 0);
	/* Setup for ADC clock rate */
	Chip_ADC_SetClockRate(LPC_ADC0, 500000);
	/* For ADC0, sequencer A will be used without threshold events.
It will be triggered manually, convert CH8 and CH10 in the sequence */
	Chip_ADC_SetupSequencer(LPC_ADC0, ADC_SEQA_IDX, (ADC_SEQ_CTRL_CHANSEL(8) | ADC_SEQ_CTRL_CHANSEL(10) | ADC_SEQ_CTRL_MODE_EOS));
	// fix this and check if this is needed
	Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 0, (IOCON_MODE_INACT | IOCON_ADMODE_EN));
	/* For ADC0, select analog input pin for channel 0 on ADC0 */
	Chip_ADC_SetADC0Input(LPC_ADC0, 0);
	/* Use higher voltage trim for both ADC */
	Chip_ADC_SetTrim(LPC_ADC0, ADC_TRIM_VRANGE_HIGHV);
	/* Assign ADC0_8 to PIO1_0 via SWM (fixed pin) and ADC0_10 to PIO0_0 */
	Chip_SWM_EnableFixedPin(SWM_FIXED_ADC0_8);
	/* Need to do a calibration after initialization and trim */
	//while (!(Chip_ADC_IsCalibrationDone(LPC_ADC0))); // The NXP library function violates their own access rules given in data sheet so we can't use it
	ADC_StartCalibration(LPC_ADC0);
	/* Set maximum clock rate for ADC */
	/* Our CPU clock rate is 72 MHz and ADC clock needs to be 50 MHz or less
	 * so the divider must be at least two. The real divider used is the value below + 1
	 */
	Chip_ADC_SetDivider(LPC_ADC0, 1);
	/* Chip_ADC_SetClockRate set the divider but due to rounding error it sets the divider too low
	 * which results in a clock rate that is out of allowed range
	 */
	//Chip_ADC_SetClockRate(LPC_ADC0, 500000); // does not work with 72 MHz clock when we want maximum frequency
	/* Clear all pending interrupts and status flags */
	Chip_ADC_ClearFlags(LPC_ADC0, Chip_ADC_GetFlags(LPC_ADC0));
	/* Enable sequence A completion interrupts for ADC0 */
	Chip_ADC_EnableInt(LPC_ADC0, ADC_INTEN_SEQA_ENABLE);
	/* We don't enable the corresponding interrupt in NVIC so the flag is set but no interrupt is triggered */
	/* Enable sequencer */
	Chip_ADC_EnableSequencer(LPC_ADC0, ADC_SEQA_IDX);
	/* Configure systick timer */
	SysTick_Config(Chip_Clock_GetSysTickClockRate() / TICKRATE_HZ);
	uint32_t a0;
	uint32_t d0;
	char str[80];
	while(1) {
		Chip_ADC_StartSequencer(LPC_ADC0, ADC_SEQA_IDX);
		// poll sequence complete flag
		while(!(Chip_ADC_GetFlags(LPC_ADC0) & ADC_FLAGS_SEQA_INT_MASK));
		// clear the flags
		Chip_ADC_ClearFlags(LPC_ADC0, Chip_ADC_GetFlags(LPC_ADC0));
		// get data from ADC channels
		a0 = Chip_ADC_GetDataReg(LPC_ADC0, 8); // raw value
		d0 = ADC_DR_RESULT(a0); // ADC result with status bits masked to zero and shifted to start from zero
		TC74RegisterData[0] = 0;
		SetupXferRecAndExecute(I2C_TEMP_ADDR_7BIT, &TC74RegisterData[0], 1, &TC74RegisterData[1], 1);


		int difference = d0 * 166 / 4095 - 40 - (int8_t)TC74RegisterData[1];

		if (difference) {
			green.write(false);
			blink_period = 50 * 192 / abs(difference);
			if(difference < 0 && BlinkingLED != &blue) {
				BlinkingLED->write(false);
				BlinkingLED = &blue;
			} else if (difference > 0 && BlinkingLED != &red) {
				BlinkingLED->write(false);
				BlinkingLED = &red;
			}
		} else {
			blink_period = 0;
			if (difference == 0 && BlinkingLED != &green) {
				BlinkingLED->write(false);
				green.write(true);
				BlinkingLED = nullptr;
			}
		}
		sprintf(str, "difference = %d, temperature = %d, blinking period = %d\n", difference, TC74RegisterData[1], blink_period.load() );
		ITM_write(str);
		lcd.setCursor(0,0);
		sprintf(str, "%4ld", d0);
		lcd.print(str);
		lcd.setCursor(5,0);
		bargraph.draw(d0 * 50 / 4095);
		lcd.setCursor(0,1);
		sprintf(str, "%4d", (int8_t)TC74RegisterData[1]);
		lcd.print(str);
		lcd.setCursor(5,1);
		bargraph.draw((int8_t)TC74RegisterData[1] * 50 / 30);

		Sleep(100);
	}
	return 0 ;
}
