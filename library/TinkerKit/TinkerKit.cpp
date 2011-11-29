#include "TinkerKit.h"


TinkerKit::TinkerKit()
{}

/*
 * Buttons Class and Methods
 */  

TKButton::TKButton(uint8_t pin) : DigitalInput(pin) 
{
	_toggleState = false;
	_oldState = false;
}

boolean TKButton::toggle()
{
	boolean currentState = state();
	if( (currentState == HIGH) && (_oldState == LOW) )	
		_toggleState = !_toggleState;
	_oldState = currentState;
	
	return _toggleState;
}

/*
 * Tilt Sensor Class and Methods
 */  
  
TKTiltSensor::TKTiltSensor(uint8_t pin) : DigitalInput(pin) {} 

/*
 * Touch Sensor Class and Methods
 */  
  
TKTouchSensor::TKTouchSensor(uint8_t pin) : DigitalInput(pin) {} 
  
/*
 * Leds Class and Methods
 */  

TKLed::TKLed(uint8_t pin) : DigitalOutput(pin), AnalogOutput(pin) { _prevMillis = 0; _state = LOW; }

void TKLed::blink(unsigned long _interval) 
{
	if(millis() - _prevMillis > _interval)
	{
		_prevMillis = millis();
		_state = !_state;
	}
	set(_state);
} 

/*
 * Potentiometer Class and Methods
 */
  
TKPotentiometer::TKPotentiometer(uint8_t pin) : AnalogInput(pin) {}

/*
 * LightSensor Class and Methods
 */
  
TKLightSensor::TKLightSensor(uint8_t pin) : AnalogInput(pin) {}

/*
 * Thermistor Class and Methods
 */
  
TKThermistor::TKThermistor(uint8_t pin) : AnalogInput(pin) {}

float TKThermistor::getCelsius()
{
	float Rthermistor = Rb * (ADCres / TKThermistor::rawData() - 1);
	float _temperatureC = Beta / (log( Rthermistor * Ginf )) ;
		
	return _temperatureC - Kelvin;
}

float TKThermistor::getFahrenheit()
{
	float _temperatureF = (TKThermistor::getCelsius() * 9.0)/ 5.0 + 32.0; ;
	
	return _temperatureF;
}

/*
 * MosFet Class and Methods
 */
  
TKMosFet::TKMosFet(uint8_t pin) : DigitalOutput(pin), AnalogOutput(pin) {}

/*
 * Relay Class and Methods
 */
  
TKRelay::TKRelay(uint8_t pin) : DigitalOutput(pin) {}
