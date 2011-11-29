#include "AnalogInput.h"

AnalogInput::AnalogInput(uint8_t pin)
{
	_pin = pin;	
}

int AnalogInput::rawData()
{
	return analogRead(_pin);
}