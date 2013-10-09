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

boolean TKDigital::read() {
    
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

int TKAnalog::read() {

    int val;
    
    #if USB_VID == 0x2341 && USB_PID == 0x803C
        val = Esplora.readTK(pin);
    #else
        val = analogRead(pin);
    #endif          

    if (val > _oldVal)
    {
      _increasing = true;
      _decreasing = false;
    }

    if (val < _oldVal)
    {
      _increasing = false;
      _decreasing = true;
    }

    _oldVal = val;
       
    return val;    
}

boolean TKAnalog::increasing() {
    TKAnalog::read();
    return _increasing;
}

boolean TKAnalog::decreasing() {
    TKAnalog::read();
    return _decreasing;
}

/*      Analog Input with two connectors       */

TKAnalog2::TKAnalog2(uint8_t _pinX, uint8_t _pinY)
{
    pinX = _pinX;
    pinY = _pinY;
}

TKAnalog2::TKAnalog2(uint8_t _pinX, uint8_t _pinY, uint8_t _pinZ)
{
    pinX = _pinX;
    pinY = _pinY;
    pinZ = _pinZ;
}

int TKAnalog2::readX() {
    
    int val;
    
    #if USB_VID == 0x2341 && USB_PID == 0x803C
        val = Esplora.readTK(pinX);
    #else
        val = analogRead(pinX);
    #endif
    
    return val;
}

int TKAnalog2::readY() {
    
    int val;
    
    #if USB_VID == 0x2341 && USB_PID == 0x803C
        val = Esplora.readTK(pinY);
    #else
        val = analogRead(pinY);
    #endif
    
    return val;
}

int TKAnalog2::readZ() {
    
    int val;
    
    #if USB_VID == 0x2341 && USB_PID == 0x803C
        val = Esplora.readTK(pinZ);
    #else
        val = analogRead(pinZ);
    #endif
    
    return val;
}

/*      Output       */

TKOutput::TKOutput(uint8_t _pin)
{
    pin = _pin;
	_state = LOW;
	pinMode(pin, OUTPUT);
}

void TKOutput::write(int value)
{
    if( value <= TK_MAX && value >= 0 )
        analogWrite(pin, value * 0.25);
    else
        return;
}

void TKOutput::blink(int del)
{
    on();
    delay(del);
    off();
    delay(del);
}

void TKOutput::blink(int del1, int del2)
{
    on();
    delay(del1);
    off();
    delay(del2);
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
    _heldTime = 500;
}

void TKButton::update() {
  boolean newState = TKButton::read();
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
      
      int timeDiff = millis() - _millisMark;
      
      if(newState == HIGH && _oldState == HIGH && timeDiff > _heldTime) {
  		_heldState = true;
  	} else {
  		_heldState = false;
  	}

  	
  }
}


boolean TKButton::readSwitch()
{
	TKButton::update();
	return _toggleState;
}

boolean TKButton::pressed()
{
	TKButton::update();

	if(_pressedState == true)
	{
        _millisMark = millis();
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
  
TKTiltSensor::TKTiltSensor(uint8_t _pin) : TKDigital (_pin){}

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

int TKPotentiometer::read()
{

    int val = TKAnalog::read();

	if (val < _minVal) {_minVal = val;}
	if (val > _maxVal) {_maxVal = val;}

	_mappedVal = map(val, _minVal, _maxVal, 0, 1023);
	_mappedVal = constrain(_mappedVal, 0, 1023);
	
	return _mappedVal;
}

int TKPotentiometer::readStep(int steps) {
	
	_steps = steps;

	int step  = floor(map(read(), 0, 1023, 0, _steps));
	
	return step;		
}

 
/*      Light Sensor        */

TKLightSensor::TKLightSensor(uint8_t _pin) : TKAnalog(_pin){}

/*      Temperature Sensor       */
  
TKThermistor::TKThermistor(uint8_t _pin) : TKAnalog(_pin) {}

float TKThermistor::readCelsius()
{
	float Rthermistor = Rb * (ADCres / TKThermistor::read() - 1);
	float _temperatureC = Beta / (log( Rthermistor * Ginf )) ;

	return _temperatureC - Kelvin;
}

float TKThermistor::readFahrenheit()
{
	float _temperatureF = (TKThermistor::readCelsius() * 9.0)/ 5.0 + 32.0; ;

	return _temperatureF;
}


/*      Hall Sensor     */

TKHallSensor::TKHallSensor(uint8_t _pin) : TKAnalog(_pin) {}

boolean TKHallSensor::polarity()
{ 
	int value = read();
	if( value >= _zeroValue  )
		return NORTH;
	else
		return SOUTH;
}

/*      Joystick        */
  
TKJoystick::TKJoystick(uint8_t _pinX, uint8_t _pinY) : TKAnalog2 (_pinX, _pinY){}

int TKJoystick::readX()
{
    
    int val = TKAnalog2::readX();
    
	if (val < _minVal) {_minVal = val;}
	if (val > _maxVal) {_maxVal = val;}
    
	_mappedVal = map(val, _minVal, _maxVal, 0, 1023);
	_mappedVal = constrain(_mappedVal, 0, 1023);
	
	return _mappedVal;
}

int TKJoystick::readY()
{
    
    int val = TKAnalog2::readY();
    
	if (val < _minVal) {_minVal = val;}
	if (val > _maxVal) {_maxVal = val;}
    
	_mappedVal = map(val, _minVal, _maxVal, 0, 1023);
	_mappedVal = constrain(_mappedVal, 0, 1023);
	
	return _mappedVal;
}


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
   	_yZeroVoltage += readY();
   	_xZeroVoltage += readX();
   	delay(20);
   }
   _yZeroVoltage /= 50;	 
   _xZeroVoltage /= 50;	
}

long TKGyro::readXAxisRate()
{	
 	return ((long)(readX() - _xZeroVoltage) * _sensitivityInCount) / 1000;
}
 
long TKGyro::readYAxisRate()
{
	return ((long)(readY() - _yZeroVoltage) * _sensitivityInCount) / 1000;
}
 
 
 /*
  * Accelerometer Class and Methods
  */
  
TKAccelerometer::TKAccelerometer(uint8_t _pinX, uint8_t _pinY) : TKAnalog2(_pinX,_pinY){}
TKAccelerometer::TKAccelerometer(uint8_t _pinX, uint8_t _pinY, uint8_t _pinZ) : TKAnalog2(_pinX,_pinY,_pinZ){}

int TKAccelerometer::inclination()
{
	int xVal = readX() - _zeroOffset;
	int yVal = readY() - _zeroOffset;

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