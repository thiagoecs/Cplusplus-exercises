#ifndef MORSESENDER_H_
#define MORSESENDER_H_

#include "board.h"
#include "DigitalIoPin.h"
#include <string>
#include <atomic>
#include "Sleep.h"
#define DOTLEN 20



class MorseSender {
public:
	MorseSender(DigitalIoPin* led, DigitalIoPin* decoder);
	virtual ~MorseSender(){};
	void converter(char *buffer);
	void converter(std::string &input);
private:
	DigitalIoPin *led, *decoder;

};

const int DOT = 1;
const int DASH = 3;
struct MorseCode {
	char symbol;
	unsigned char code[7];
};
const MorseCode ITU_morse[] = {
		{ 'A', { DOT, DASH } }, // A
		{ 'B', { DASH, DOT, DOT, DOT } }, // B
		{ 'C', { DASH, DOT, DASH, DOT } }, // C
		{ 'D', { DASH, DOT, DOT } }, // D
		{ 'E', { DOT } }, // E
		{ 'F', { DOT, DOT, DASH, DOT } }, // F
		{ 'G', { DASH, DASH, DOT } }, // G
		{ 'H', { DOT, DOT, DOT, DOT } }, // H
		{ 'I', { DOT, DOT } }, // I
		{ 'J', { DOT, DASH, DASH, DASH } }, // J
		{ 'K', { DASH, DOT, DASH } }, // K
		{ 'L', { DOT, DASH, DOT, DOT } }, // L
		{ 'M', { DASH, DASH } }, // M
		{ 'N', { DASH, DOT } }, // N
		{ 'O', { DASH, DASH, DASH } }, // O
		{ 'P', { DOT, DASH, DASH, DOT } }, // P
		{ 'Q', { DASH, DASH, DOT, DASH } }, // Q
		{ 'R', { DOT, DASH, DOT } }, // R
		{ 'S', { DOT, DOT, DOT } }, // S
		{ 'T', { DASH } }, // T
		{ 'U', { DOT, DOT, DASH } }, // U
		{ 'V', { DOT, DOT, DOT, DASH } }, // V
		{ 'W', { DOT, DASH, DASH } }, // W
		{ 'X', { DASH, DOT, DOT, DASH } }, // X
		{ 'Y', { DASH, DOT, DASH, DASH } }, // Y
		{ 'Z', { DASH, DASH, DOT, DOT } }, // Z
		{ '0', { DASH, DASH, DASH, DASH, DASH } }, // 0
		{ '1', { DOT, DASH, DASH, DASH, DASH } }, // 1
		{ '2', { DOT, DOT, DASH, DASH, DASH } }, // 2
		{ '3', { DOT, DOT, DOT, DASH, DASH } }, // 3
		{ '4', { DOT, DOT, DOT, DOT, DASH } }, // 4
		{ '5', { DOT, DOT, DOT, DOT, DOT } }, // 5
		{ '6', { DASH, DOT, DOT, DOT, DOT } }, // 6
		{ '7', { DASH, DASH, DOT, DOT, DOT } }, // 7
		{ '8', { DASH, DASH, DASH, DOT, DOT } }, // 8
		{ '9', { DASH, DASH, DASH, DASH, DOT } }, // 9
		{ 0, { 0 } } // terminating entry - Do not remove!
};

#endif /* MORSESENDER_H_ */
