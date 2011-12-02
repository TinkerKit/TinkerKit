#include "TinkerKit.h"


AnalogOutput::AnalogOutput(uint8_t pin)
{
	_pin = pin;	
	_PWMvalue = 0;
}

void AnalogOutput::set(int PWMvalue)
{
	if( PWMvalue <= TK_MAX )
	{
		_PWMvalue = PWMvalue;
		analogWrite(_pin, _PWMvalue/4);
	} else {
		return;
	}
}
