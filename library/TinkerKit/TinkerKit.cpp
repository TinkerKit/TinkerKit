#include "TinkerKit.h"

#if USB_VID == 0x2341 && USB_PID == 0x803C
#include <Esplora.h>
#endif

/*
 -----------------------------------------------------------------------------
                                    Generals
 -----------------------------------------------------------------------------
 */

/*      Digital Input       */

TKDigital::TKDigital(uint8_t _pin)
{
    pin = _pin;
    pinMode(pin, INPUT);
}

boolean TKDigital::get() {
    
    boolean val;
    
    #if USB_VID == 0x2341 && USB_PID == 0x803C
        int value = Esplora.readTK(pin);
        if (value < 128)
            val = 0;
        else
            val = 1;
    #else
        val = digitalRead(pin);
    #endif
    
    return val;
}


/*      Analog Input        */

TKAnalog::TKAnalog(uint8_t _pin)
{
    pin = _pin;
}

int TKAnalog::get() {

    int val;
    
    #if USB_VID == 0x2341 && USB_PID == 0x803C
        val = Esplora.readTK(pin);
    #else
        val = analogRead(pin);
    #endif
    
    return val;
}

/*      Analog Input with two connectors       */

TKAnalog2::TKAnalog2(uint8_t _pinX, uint8_t _pinY)
{
    pinX = _pinX;
    pinY = _pinY;
}

int TKAnalog2::getXAxis() {
    
    int val;
    
    #if USB_VID == 0x2341 && USB_PID == 0x803C
        val = Esplora.readTK(pinX);
    #else
        val = analogRead(pinX);
    #endif
    
    return val;
}

int TKAnalog2::getYAxis() {
    
    int val;
    
    #if USB_VID == 0x2341 && USB_PID == 0x803C
        val = Esplora.readTK(pinY);
    #else
        val = analogRead(pinY);
    #endif
    
    return val;
}

TKOutput::TKOutput(uint8_t _pin)
{
    pin = _pin;
	_state = LOW;
	pinMode(pin, OUTPUT);
}

void TKOutput::set(int value)
{
    if( value <= TK_MAX && value >= 0 )
        analogWrite(pin, value * 0.25);
    else
        return;
}

/*
 -----------------------------------------------------------------------------
                                Digital Inputs
 -----------------------------------------------------------------------------
 */

/*      Button      */

TKButton::TKButton(uint8_t _pin) : TKDigital(_pin)
{
	_toggleState = LOW;
	_oldState = LOW;
	_pressedState = LOW;
	_releasedState = LOW;
	_heldState = LOW;
}

void TKButton::update() {
  boolean newState = TKButton::get();
  if (newState != _oldState) {
    // pressed?
    if (newState == HIGH) {
      _pressedState = true;      
    }
    else {
      _releasedState = true;
     _toggleState = !_toggleState;	  
    }
    
    _oldState = newState;
    delay(50); // debouncing
  } 

  else {

  	if(newState == HIGH && _oldState == HIGH) {
  		_heldState = true;
  	} else {
  		_heldState = false;
  	}

  	
  }
}


boolean TKButton::getSwitch()
{
	TKButton::update();
	return _toggleState;
}

boolean TKButton::pressed()
{
	TKButton::update();

	if(_pressedState == true)
	{
		_pressedState = false;
		return true;
	}		
	else
		return false;
}

boolean TKButton::released()
{
	TKButton::update();

	if(_releasedState == true)
	{
		_releasedState = false;
		return true;
	}		
	else
		return false;
}

boolean TKButton::held()
{	
	TKButton::update();
	return _heldState;
}


/*      Tilt Sensor         */
  
TKTiltSensor::TKTiltSensor(uint8_t _pin) : TKDigital (_pin)
{
}


/*      Touch Sensor        */
  
 TKTouchSensor::TKTouchSensor(uint8_t _pin) : TKButton(_pin) {}

/*
 -----------------------------------------------------------------------------
                                Analog Inputs
 -----------------------------------------------------------------------------
 */

/*      Potentiometer       */

TKPotentiometer::TKPotentiometer(uint8_t _pin) : TKAnalog(_pin)

{
	pin = _pin;
	_minVal = 1023;
	_maxVal = 0;
}

int TKPotentiometer::get()
{

    int val = TKAnalog::get();

	if (val < _minVal) {_minVal = val;}
	if (val > _maxVal) {_maxVal = val;}

	_mappedVal = map(val, _minVal, _maxVal, 0, 1023);
	_mappedVal = constrain(_mappedVal, 0, 1023);
	
	return _mappedVal;
}

int TKPotentiometer::getStep(int steps) {
	
	_steps = steps;

	int step  = floor(map(get(), 0, 1023, 0, _steps));
	
	return step;		
}

 
/*      Light Sensor        */

TKLightSensor::TKLightSensor(uint8_t _pin) : TKAnalog(_pin){}

/*      Temperature Sensor       */
  
TKThermistor::TKThermistor(uint8_t _pin) : TKAnalog(_pin) {}

float TKThermistor::getCelsius()
{
	float Rthermistor = Rb * (ADCres / TKThermistor::get() - 1);
	float _temperatureC = Beta / (log( Rthermistor * Ginf )) ;

	return _temperatureC - Kelvin;
}

float TKThermistor::getFahrenheit()
{
	float _temperatureF = (TKThermistor::getCelsius() * 9.0)/ 5.0 + 32.0; ;

	return _temperatureF;
}


/*      Hall Sensor     */

TKHallSensor::TKHallSensor(uint8_t _pin) : TKAnalog(_pin) {}

boolean TKHallSensor::polarity()
{ 
	int value = get();
	if( value >= _zeroValue  )
		return NORTH;
	else
		return SOUTH;
}

/*      Joystick        */
  
TKJoystick::TKJoystick(uint8_t _pinX, uint8_t _pinY) : TKAnalog2 (_pinX, _pinY){}


/*      Gyro        */

TKGyro::TKGyro(uint8_t _pinX, uint8_t _pinY, boolean model) : TKAnalog2 (_pinX, _pinY)
{

 	_sensitivityInCount = 14633;  // 4.88mV / (0.167mV/dps * 2)
 	
 	if(model == TK_X4)
 		_sensitivityInCount /= 4;

    // default values
    _xZeroVoltage = 503;	// 2.46V expressed in ADC counts
    _yZeroVoltage = 503;
}

void TKGyro::calibrate()
{  
	_xZeroVoltage = 0;	
	_yZeroVoltage = 0;

	for (uint8_t i=0; i<50; i++)
   {
   	_yZeroVoltage += getYAxis();
   	_xZeroVoltage += getXAxis();
   	delay(20);
   }
   _yZeroVoltage /= 50;	 
   _xZeroVoltage /= 50;	
}

long TKGyro::getXAxisRate()
{	
 	return ((long)(getXAxis() - _xZeroVoltage) * _sensitivityInCount) / 1000;
}
 
long TKGyro::getYAxisRate()
{
	return ((long)(getYAxis() - _yZeroVoltage) * _sensitivityInCount) / 1000;
}
 
 
 /*
  * Accelerometer Class and Methods
  */
  
TKAccelerometer::TKAccelerometer(uint8_t _pinX, uint8_t _pinY) : TKAnalog2(_pinX,_pinY){}

int TKAccelerometer::inclination()
{
	int xVal = getXAxis() - _zeroOffset;
	int yVal = getYAxis() - _zeroOffset;

	if(xVal <= 96 && yVal <= 96)
	{
		int inclination = atan2(xVal, yVal)*180/M_PI;
		return (int) inclination;
	} else {
		return NULL;
	}
}

/*
-----------------------------------------------------------------------------
                                        Outputs
-----------------------------------------------------------------------------
*/

/* LED */

TKLed::TKLed(uint8_t _pin) : TKOutput(_pin) {}


/* MosFet */

TKMosFet::TKMosFet(uint8_t _pin) : TKOutput(_pin) {}


/* Relay */

TKRelay::TKRelay(uint8_t _pin) : TKOutput(_pin) {}