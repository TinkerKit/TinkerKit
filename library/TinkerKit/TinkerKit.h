
/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include "Arduino.h"



#ifndef TinkerKit_h
#define TinkerKit_h


// Minimum Analog In/Out that each platform have
#define I0 A0
#define I1 A1
#define I2 A2
#define I3 A3
#define I4 A4
#define I5 A5

#define O0 11
#define O1 10
#define O2 9
#define O3 6
#define O4 5
#define O5 3

// Mega have more I/O
#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__)
#define I6 A6
#define I7 A7
#define I8 A8
#define I9 A9

#define D13 13
#define D12 12
#define D8 8
#define D7 7
#define D4 4
#define D2 2
#endif

#define TK_MAX 1023
#define TK_X1 0	// identifies the 1x TKGyro model
#define TK_X4 1	// identifies the 4x TKGyro model


class DigitalInput
{
	public:
		DigitalInput(uint8_t pin);
		boolean get();
	
	protected:
		boolean _pin;
};

/*
 * Digital Output Class
 */
 
class DigitalOutput
{
	public:
		DigitalOutput(uint8_t pin);
		void set(boolean _value);		
		boolean state();
	
	protected:
		boolean _pin;
		boolean _state;
};

/*
 * Analog Input Class
 */
 
class AnalogInput 
{
	public:
		AnalogInput(uint8_t pin);
		int get();
		
	protected:
		uint8_t _pin;
};

/*
 *Analog Output Class
 */
 
class AnalogOutput 
{
	public:
		AnalogOutput(uint8_t _pin);
		void set(int _PWMvalue);
		
	protected:
		uint8_t _pin;
		int _PWMvalue;
};


/* 
-----------------------------------------------------------------------------
                        TinkerKit modules Classes
-----------------------------------------------------------------------------
*/


/*
 * Buttons Class and Methods
 */
  
class TKButton : public DigitalInput
{
	public:
		TKButton(uint8_t pin);
		boolean toggle();
		boolean pressed();
		boolean held();
		boolean released();
		
	protected:
		boolean _toggleState, _oldState;
};

/*
 * Tilt Sensor Class and Methods
 */
 
class TKTiltSensor : public DigitalInput
{
	public:
		TKTiltSensor(uint8_t pin);
};

/*
 * Touch Sensor Class and Methods
 */  
 
class TKTouchSensor : public DigitalInput
{
	public:
		TKTouchSensor(uint8_t pin);
};

/*
 * Leds Class and Methods
 */ 
 
class TKLed : public DigitalOutput, AnalogOutput
{
	public: 
		TKLed(uint8_t pin);
		inline void on() { DigitalOutput::set(HIGH); }
		inline void off() { DigitalOutput::set(LOW); }
		inline void brightness(int value) { AnalogOutput::set(value); }
		void blink(unsigned long _interval);
		void fade(int startValue,int stopValue, unsigned long _interval);
		
	protected:
		unsigned long _prevMillis;
		uint8_t _currentFade;		
		unsigned long _timeStep;
		boolean _init;
		int8_t _direction;
};	

/*
 * Potentiometer Class and Methods
 */
 
class TKPotentiometer : public AnalogInput
{
	public:
		TKPotentiometer(uint8_t pin);
};


/*
 * LightSensor Class and Methods
 */

class TKLightSensor : public AnalogInput
{
	public:
		TKLightSensor(uint8_t pin);
};

/*
 * Thermistor Class and Methods
 */
 
class TKThermistor : public AnalogInput
{
	public:
		TKThermistor(uint8_t pin);
		float getCelsius();
		float getFahrenheit();
		
	protected:
		const static float ADCres = 1023.0;
		const static int Beta = 3950;			// Beta parameter
		const static float Kelvin = 273.15;	// 0°C = 273.15 K
		const static int Rb = 10000;			// 10 kOhm
		const static float Ginf = 120.6685;	// Ginf = 1/Rinf
														// Rinf = R0*e^(-Beta/T0) = 4700*e^(-3950/298.15)
};	
		
/*
 * MosFet Class and Methods
 */
 
class TKMosFet : public DigitalOutput, AnalogOutput
{
	public:
		TKMosFet(uint8_t pin);
		void set(boolean value);
		inline void on() { DigitalOutput::set(HIGH); }
		inline void off() { DigitalOutput::set(LOW); }
};

/*
 * Relay Class and Methods
 */
 
class TKRelay : public DigitalOutput
{
	public:
		TKRelay(uint8_t pin);
		inline void on() { DigitalOutput::set(HIGH); }
		inline void off() { DigitalOutput::set(LOW); }
};

/*
 * Hall Sensor Class and Methods
 */

class TKHallSensor : public AnalogInput
{
	public:
		TKHallSensor(uint8_t pin);
		inline boolean state() 
		{ 
			if(TKHallSensor::get() > _zeroValue)
				return true;
			else
				return false;
		}
			
		protected:
			const static uint16_t _zeroValue = 510;
};


/*
 * Joystick Class and Methods
 */
 
 class TKJoystick
 {
 	public:
 		TKJoystick(uint8_t pinX, uint8_t pinY);
 		inline int getXAxis() { return _xAxis.get(); }
 		inline int getYAxis() { return _yAxis.get(); }
 		 		
 	protected:
 		AnalogInput _xAxis, _yAxis;
 };
 
 
/*
 * Gyro Sensor Class and Methods
 */

class TKGyro
{	
	public:
		TKGyro(uint8_t pinX, uint8_t pinY, boolean model);
		inline int getXAxis() { return _xAxis.get(); }
 		inline int getYAxis() { return _yAxis.get(); }
		int xAxisRate();
		int yAxisRate();
		
	protected:
		AnalogInput _xAxis, _yAxis;
		boolean model;
		int _amplification;
		const static int _ADCresolution = 4888;	// [mV/count]	multiplierd by 1000 to avoid float numbers
		// minimum sensitivity for the 1x module value (from datasheet is 0.167 mV/deg/s but the TinkerKit module has the outputs amplified 2x)
		const static int _sensitivity = 334;	// Sensitivity is expressed in mV/degree/seconds, multiplierd by 1000 to avoid float numbers. 
															// This value represent the sensitivity of the 1x module. The sensitivity of the 4x module is 4x of this one
		const static int _sensitivityInCount = _ADCresolution / _sensitivity;	// we obtain the sensitivity expressed in ADC counts
																										// [counts/dps]
		const static int zeroVoltage = 503;	// 2.46V expressed in ADC counts
};

/*
 * Accelerometer Class and Methods
 */
 
class TKAccelerometer
{	
	public:
		TKAccelerometer(uint8_t pinX, uint8_t pinY);
		inline int getXAxis() { return _xAxis.get(); }
 		inline int getYAxis() { return _yAxis.get(); }

		
	protected:
		AnalogInput _xAxis, _yAxis;
};

#endif


