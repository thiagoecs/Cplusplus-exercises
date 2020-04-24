/*
 * ITMwrapper1.h
 *
 *  Created on: Jan 24, 2020
 *      Author: thiag
 */

#ifndef ITM_WRAPPER_H_
#define ITM_WRAPPER_H_
#include "ITM_write.h"
#include <cstdio>

class ITM_wrapper {
public:
	ITM_wrapper() {
		ITM_init();
	}
	~ITM_wrapper();
	void print(int button, int count){
		snprintf (buffer, 100, "The button sw%d was pressed for %d ms\n", button, count );
		ITM_write(buffer);
	}
private:
	int button, count;
	char buffer[100];

};

#endif /* ITM_WRAPPER_H_ */
