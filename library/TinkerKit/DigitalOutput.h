#include "WProgram.h"

#ifndef DigitalOutput_h
#define DigitalOutput_h

class DigitalOutput
{
	public:
		DigitalOutput(uint8_t pin);
		void set(boolean _value);		
		boolean state();
	
	protected:
		boolean _pin;
		boolean _state;
};

#endif