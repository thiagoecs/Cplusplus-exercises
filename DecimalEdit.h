
#ifndef DECIMALEDIT_H_
#define DECIMALEDIT_H_

#include "PropertyEdit.h"
#include "LiquidCrystal.h"
#include <string>
#include <atomic>

class DecimalEdit: public PropertyEdit {
public:
	DecimalEdit(LiquidCrystal *lcd_, std::string editTitle, float upper, float lower, float step);
	virtual ~DecimalEdit();
	void increment();
	void decrement();
	void accept();
	void cancel();
	void setFocus(bool focus);
	bool getFocus();
	void display();
	float getValue();
	void setValue(float value);

	static std::atomic<bool> prfloat_needed;
private:
	void save();
	void displayEditValue();
	LiquidCrystal *lcd;
	std::string title;
	float value;
	float edit;
	float upper;
	float lower;
	float step;
	bool focus;
};

#endif /* DECIMALEDIT_H_ */
