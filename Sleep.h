#ifndef SLEEP_H
#define SLEEP_H
#include "board.h"
#include "chip.h"
#include <atomic>
#include "SimpleMenu.h"
#include "DigitalIoPin.h"
#define TICKRATE_HZ (1000)	/* 1000 ticks per second */

extern std::atomic_int counter, counter2, blink_period;
extern DigitalIoPin *BlinkingLED;
extern SimpleMenu *menu;

extern "C" { void SysTick_Handler(void); };

void Sleep(int ms);

void Board_Startup();
#endif
