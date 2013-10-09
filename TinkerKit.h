
/*
 *      TinkerKit Library v0.1
 *      
 *
 *
 *      created on Dec 2011
 *      by Federico Vanzati
 *
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
#define NORTH 1	// north pole: used in TKHallSensor
#define SOUTH 0	// south pole: used in TKHallSensor


/* 
-----------------------------------------------------------------------------
                                Generic Classes
-----------------------------------------------------------------------------
*/

class TKDigital
{
public:
    TKDigital(uint8_t _pin);
    boolean read();
    
protected:
    uint8_t pin;
};


class TKAnalog
{
public:
    TKAnalog(uint8_t _pin);
    int read();
    boolean increasing();
    boolean decreasing();
    
protected:
    uint8_t pin;
    int _oldVal;
    boolean _increasing;
    boolean _decreasing;    
};

class TKAnalog2
{
public:
    TKAnalog2(uint8_t _pinX, uint8_t _pinY);
    TKAnalog2(uint8_t _pinX, uint8_t _pinY, uint8_t _pinZ);
    int readX();
    int readY();
    int readZ();
    
protected:
    uint8_t pinX, pinY, pinZ;
};


class TKOutput
{
    public:
    TKOutput (uint8_t _pin);
    void write(int value);
    inline int state() { return _state; }
    void on() { 
        write(1023); 
        _state = HIGH; 
    }
    void off() { 
        write(0); 
        _state = LOW; 
    }
    void blink(int delay);
    void blink(int delay1, int delay2);
    
protected:
    uint8_t pin;
    int _state;
};

/*
 -----------------------------------------------------------------------------
                                Digital Inputs
 -----------------------------------------------------------------------------
*/


/*      Button      */
  
class TKButton: public TKDigital
{
	public:
		TKButton(uint8_t _pin);
		boolean readSwitch();
		boolean pressed();
		boolean held();
		boolean released();
		
	protected:
		boolean _toggleState, _oldState;
		boolean _pressedState, _releasedState;
		boolean _heldState;
        int _heldTime;
        int _millisMark;
		
		void update();
};


/*      Tilt Sensor     */
 
class TKTiltSensor: public TKDigital
{
	public:
		TKTiltSensor(uint8_t pin);
};

/*      Touch Sensor        */

class TKTouchSensor : public TKButton
{
	public:
		TKTouchSensor(uint8_t _pin);
};

/*
 -----------------------------------------------------------------------------
                                Analog Inputs
 -----------------------------------------------------------------------------
 */

/*      Potentiometer        */

class TKPotentiometer: public TKAnalog
{
public:
    TKPotentiometer(uint8_t pin);
    int read();
    int readStep(int steps);
    
protected:
    int _minVal, _maxVal;
    int _mappedVal;
    int _steps;
};


/*      Light Sensor        */

class TKLightSensor : public TKAnalog
{
    public:
        TKLightSensor(uint8_t _pin);
};

/*      Temperature Sensor        */

class TKThermistor : public TKAnalog
{
public:
    TKThermistor(uint8_t _pin);
    float readCelsius();
    float readFahrenheit();
    
protected:
    const static float ADCres = 1023.0;
    const static int Beta = 3950;			// Beta parameter
    const static float Kelvin = 273.15;	// 0°C = 273.15 K
    const static int Rb = 10000;			// 10 kOhm
    const static float Ginf = 120.6685;	// Ginf = 1/Rinf
    // Rinf = R0*e^(-Beta/T0) = 4700*e^(-3950/298.15)    
};

/*      Hall Sensor        */

class TKHallSensor : public TKAnalog
{
public:
    TKHallSensor(uint8_t _pin);
    boolean polarity();
    
protected:
    const static uint16_t _zeroValue = 512;
};


/*      Joystick        */

class TKJoystick : public TKAnalog2
{
public:
    TKJoystick(uint8_t _pinX, uint8_t _pinY);
    int readX();
    int readY();
protected:
    int _minVal, _maxVal;
    int _mappedVal;
};


/*      Gyro Sensor        */

class TKGyro : public TKAnalog2
{
public:
    TKGyro(uint8_t _pinX, uint8_t _pinY, boolean model);
    void calibrate();
    long readXAxisRate();
    long readYAxisRate();
    
protected:
    boolean model;
    
    //const static int _ADCresolution = 4880;	// [mV/count]	multiplierd by 1000 to avoid float numbers
    // minimum sensitivity for the 1x module value (from datasheet is 0.167 mV/deg/s but the TinkerKit module has the outputs amplified 2x)
    //const static int _sensitivity = 334;	// Sensitivity is expressed in mV/degree/seconds, multiplierd by 1000 to avoid float numbers.
    // This value represent the sensitivity of the 1x module. The sensitivity of the 4x module is 4x of this one
    long _sensitivityInCount;	// we obtain the sensitivity expressed in ADC counts
    // [counts/dps]
    int _yZeroVoltage;
    int _xZeroVoltage;
};

/*      Accelerometer        */

class TKAccelerometer : public TKAnalog2
{
public:
    TKAccelerometer(uint8_t _pinX, uint8_t _pinY);
    TKAccelerometer(uint8_t _pinX, uint8_t _pinY, uint8_t _pinZ);
    inline float readXinG() { return (float)(readX() - _zeroOffset)/96; }
    inline float readYinG() { return (float)(readY() - _zeroOffset)/96; }
    inline float readZinG() { return (float)(readZ() - _zeroOffset)/96; }
    int inclination();
    
protected:
    const static float _gain = 1.414;
    const static int _zeroOffset = 478;
};

/*
 -----------------------------------------------------------------------------
                                    Outputs
 -----------------------------------------------------------------------------
 */

/*      LED     */
 
class TKLed : public TKOutput
{
	public: 
        TKLed(uint8_t _pin);
        inline void brightness(int value) { write(value); }
};
		
/*      MosFet      */
 
class TKMosFet : public TKOutput
{
	public:
		TKMosFet(uint8_t _pin);
};

/*      Relay       */
 
class TKRelay : public TKOutput
{
	public:
		TKRelay(uint8_t _pin);
};


#endif

