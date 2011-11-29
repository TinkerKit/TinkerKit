#include "WProgram.h"

#ifndef DigitalInput_h
#define DigitalInput_h

class DigitalInput
{
	public:
		DigitalInput(uint8_t pin);
		boolean state();
	
	protected:
		boolean _pin;
};

#endif