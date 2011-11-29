#include "WProgram.h"

#ifndef  AnalogOutput_h
#define	AnalogOutput_h

class AnalogOutput 
{
	public:
		AnalogOutput(uint8_t _pin);
		void write(uint8_t _PWMvalue);
		
	protected:
		uint8_t _pin;
		uint8_t _PWMvalue;
};

#endif