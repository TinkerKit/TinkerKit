#include "DigitalInput.h"

DigitalInput::DigitalInput(uint8_t pin)
{
	_pin = pin;
	pinMode(_pin, INPUT);
}

boolean DigitalInput::state()
{
	return digitalRead(_pin); 
}