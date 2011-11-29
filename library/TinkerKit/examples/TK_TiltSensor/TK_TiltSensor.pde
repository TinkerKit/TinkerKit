
/*
 TiltSensor
 
 Turns on and off a T010111 LED Module connected to O0 (digital  
 pin 11), triggered by a T000190 Tilt Sensor attached to I0 (analog pin 0).
 
 created 2005
 by DojoDave <http://www.0j0.org>
 modified 17 Jun 2009
 by Tom Igoe
 modified 7 dec 2010
 by Davide Gomba
 modified 29 Nov 2011
 by Priya Kuber & Federico Vanzati
 
 This example code is in the public domain.
 
 */

// include the TinkerKit library
#include <TinkerKit.h> 

TKTiltSensor tilt(I0);       // creating the object 'tilt' that bleongs to the 'TKTiltSensor' class 
                             // and giving the value to the desired input pin

TKLed led(O0);               // creating the object 'led' that belongs to the 'TKLed' class 
                             // and giving the value to the desired output pin


// variables will change as they take the current value of the sensor.
int tiltState = 0;           // variable for reading the tilt Sensor status

void setup() { 
  // The 'objects' created above, eleminates the need for pinMode().
}

void loop(){

  tiltState = tilt.state();  // read the state of the tilt Sensor  value:

  // check if the tilt Sensor  is tilted.

  if (tiltState == HIGH) {   // if it is, the tiltState is HIGH
    led.on();                // turn LED on
  } 
  else {                     // if it is not, the tiltState is LOW
    led.off();               // turn LED off
  }
}


