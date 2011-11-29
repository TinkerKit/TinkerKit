#include "WProgram.h"

#ifndef  AnalogInput_h
#define AnalogInput_h

class AnalogInput 
{
	public:
		AnalogInput(uint8_t pin);
		int rawData();
		
	protected:
		uint8_t _pin;
};

#endif