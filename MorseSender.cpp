/*
 * MorseSender.cpp
 *
 *  Created on: Jan 31, 2020
 *      Author: thiag
 */

#include "MorseSender.h"


MorseSender::MorseSender(DigitalIoPin* led = nullptr, DigitalIoPin* decoder = nullptr): led {led}, decoder {decoder} {}

void MorseSender::converter(char *buffer){
	for(int i = 0; buffer[i]; i++){
		int index {0};

		if (isalpha(buffer[i])){
			index = buffer [i] - 65;
		}
		else if (isdigit(buffer[i])){
			index = buffer [i] - 22;
		}
		else if(isspace(buffer[i])){
			Sleep(DOTLEN * 2);
			index = 36;
		}
		else
			index = 23;

		for(int i = 0; ITU_morse[index].code[i]; i++){
			led->write(true);
			decoder->write(true);
			Sleep(DOTLEN * ITU_morse[index].code[i]);
			led->write(false);
			decoder->write(false);
			Sleep(DOTLEN);

		}
		if(buffer[i+1] != '\0'){
			Sleep(DOTLEN * 2);
		}
	}
}
void MorseSender::converter(std::string &input){
	for(auto &letter: input){
		int index {0};

		if (isalpha(letter)){
			index = letter - 65;
		}
		else if (isdigit(letter)){
			index = letter - 22;
		}
		else if(isspace(letter)){
			Sleep(DOTLEN * 2);
			index = 36;
		}
		else
			index = 23;

		for(int i = 0; ITU_morse[index].code[i]; i++){
			led->write(true);
			decoder->write(true);
			Sleep(DOTLEN * ITU_morse[index].code[i]);
			led->write(false);
			decoder->write(false);
			Sleep(DOTLEN);

		}
		Sleep(DOTLEN * 2);
	}
}





