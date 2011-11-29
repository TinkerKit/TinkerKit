
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

#include "WProgram.h"



#ifndef TinkerKit_h
#define TinkerKit_h

#include "DigitalInput.h"
#include "DigitalOutput.h"
#include "AnalogInput.h"
#include "AnalogOutput.h"

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


class TinkerKit
{

public:
	// Initialise
  TinkerKit(); 
  
protected:
};

/*
 * Buttons Class and Methods
 */
  
class TKButton : public DigitalInput
{
	public:
		TKButton(uint8_t pin);
		//debounce();
		boolean toggle();
	
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
		inline void on() { set(HIGH); }
		inline void off() { set(LOW); }
		void blink(unsigned long _interval);
		
		unsigned long _prevMillis;
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
};

/*
 * Relay Class and Methods
 */
 
class TKRelay : public DigitalOutput
{
	public:
		TKRelay(uint8_t pin);
};

/*
 * Hall Sensor Class and Methods
 */
 
#endif


