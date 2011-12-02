#include "TinkerKit.h"

DigitalInput::DigitalInput(uint8_t pin)
{
	_pin = pin;
	pinMode(_pin, INPUT);
}

boolean DigitalInput::get()
{
	return digitalRead(_pin); 
}