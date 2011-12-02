#include "TinkerKit.h"

DigitalOutput::DigitalOutput(uint8_t pin)
{
	_pin = pin;
	_state = LOW;
	pinMode(_pin, OUTPUT);
}

void DigitalOutput::set(boolean value)
{
	digitalWrite(_pin, value);
	_state = value;
}

boolean DigitalOutput::state()
{
	return _state;
}