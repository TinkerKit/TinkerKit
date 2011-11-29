#include "AnalogOutput.h"

#define MAX_PWM_VAL 255

AnalogOutput::AnalogOutput(uint8_t pin)
{
	_pin = pin;	
	_PWMvalue = 0;
}

void AnalogOutput::write(uint8_t PWMvalue)
{
	if( PWMvalue <= MAX_PWM_VAL )
	{
		_PWMvalue = PWMvalue;
		analogWrite(_pin, _PWMvalue);
	} else {
		return;
	}
}