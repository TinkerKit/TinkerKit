#include "TinkerKit.h"


/*
 * Buttons Class and Methods
 */  

TKButton::TKButton(uint8_t pin) : DigitalInput(pin) 
{
	_toggleState = LOW;
	_oldState = LOW;
}

boolean TKButton::toggle()
{
	boolean currentState = DigitalInput::get();
	
	if( (currentState == HIGH) && (_oldState == LOW) )	
		_toggleState = !_toggleState;
	_oldState = currentState;
	
	return _toggleState;
}

boolean TKButton::pressed()
{
	boolean currentState = DigitalInput::get();
	
	if(currentState == HIGH && _oldState == LOW)
	{
		_oldState = currentState;
		delay(50);
		return true;
	}		
	else
		return false;
}

boolean TKButton::released()
{
	boolean currentState = DigitalInput::get();
	
	if(currentState == LOW && _oldState == HIGH)
	{
		_oldState = currentState;
		delay(50);
		return true;		
	}
	else
		return false;
}

boolean TKButton::held()
{	
	if(released() == LOW && _oldState == HIGH)
		return true;		
	else
		return false;
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

TKLed::TKLed(uint8_t pin) : DigitalOutput(pin), AnalogOutput(pin) { _prevMillis = 0; _state = LOW; _init = false; }

void TKLed::blink(unsigned long _interval) 
{
	if(millis() - _prevMillis > _interval)
	{
		_prevMillis = millis();
		_state = !_state;
	}
	DigitalOutput::set(_state);
} 

void TKLed::fade(int startValue, int stopValue, unsigned long interval)
{
	if(!_init)
	{
		startValue /= 4;
		stopValue  /= 4;
		if(startValue <= stopValue)
			_direction = 1;
		else
			_direction = -1;
		
		_currentFade = startValue;
		_timeStep  = interval / abs(stopValue - startValue);
		_prevMillis = millis();
		_init = true;	
	}
	
	else if( (millis() - _prevMillis > _timeStep) && (_currentFade != stopValue) )
	{
		_prevMillis = millis();
		_currentFade += _direction;
	}
		
	AnalogOutput::set(_currentFade);
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
	float Rthermistor = Rb * (ADCres / AnalogInput::get() - 1);
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

/*
 * Hall Sensor Class and Methods
 */

TKHallSensor::TKHallSensor(uint8_t pin) : AnalogInput(pin) {}


 /*
  * Joystick Class and Methods
  */
  
TKJoystick::TKJoystick(uint8_t pinX, uint8_t pinY) : _xAxis(pinX), _yAxis(pinY) {}

 /*
  * Gyro Sensor Class and Methods
  */

TKGyro::TKGyro(uint8_t pinX, uint8_t pinY, boolean model) : _xAxis(pinX), _yAxis(pinY)
 {
 	if(model)
 		_amplification = 4;
 	else
 		_amplification = 1;
 }
 
 int TKGyro::xAxisRate()
 {
 		return (_xAxis.get() - zeroVoltage) * _sensitivityInCount / _amplification;
 }
 
  int TKGyro::yAxisRate()
 {
 		return (_yAxis.get() - zeroVoltage) * _sensitivityInCount / _amplification;
 }
 
  /*
  * Accelerometer Class and Methods
  */
  
TKAccelerometer::TKAccelerometer(uint8_t pinX, uint8_t pinY) : _xAxis(pinX), _yAxis(pinY) {}