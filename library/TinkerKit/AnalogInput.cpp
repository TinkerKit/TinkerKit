#include "TinkerKit.h"

AnalogInput::AnalogInput(uint8_t pin)
{
	_pin = pin;	
}

int AnalogInput::get()
{
	return analogRead(_pin);
}