

#include "DecimalEdit.h"
#include <cstdio>

std::atomic<bool> DecimalEdit::prfloat_needed{ false };

DecimalEdit::DecimalEdit(LiquidCrystal *lcd_, std::string editTitle, float upper, float lower, float step): lcd(lcd_), title(editTitle),upper(upper),lower(lower),step(step) {
	value = lower;
	edit = lower;
	focus = false;
}

DecimalEdit::~DecimalEdit() {
}

void DecimalEdit::increment() {
	if((edit += step) > upper){
		edit = upper;
	}
}

void DecimalEdit::decrement() {
	if((edit -= step) < lower){
		edit = lower;
	}
}

void DecimalEdit::accept() {
	save();
	prfloat_needed = true;
}

void DecimalEdit::cancel() {
	edit = value;
}


void DecimalEdit::setFocus(bool focus) {
	this->focus = focus;
}

bool DecimalEdit::getFocus() {
	return this->focus;
}

void DecimalEdit::display() {
	lcd->clear();
	lcd->setCursor(0,0);
	lcd->print(title);
	lcd->setCursor(0,1);
	char s[17];
	if(focus) {
		snprintf(s, 17, "     [%3.1f]     ", edit);
	}
	else {
		snprintf(s, 17, "      %3.1f      ", edit);
	}
	lcd->print(s);
}


void DecimalEdit::save() {
	// set current value to be same as edit value
	value = edit;
	// todo: save current value for example to EEPROM for permanent storage
}


float DecimalEdit::getValue() {
	return value;
}
void DecimalEdit::setValue(float value) {
	edit = value;
	save();
}


