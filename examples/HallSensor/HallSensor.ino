/*
 The Hall Sensor [T000070] is connected to I0 and it's
 able to detect the magnetic field polarity.
 This sketch turns on and off an LED using 
 the polarity of a magnet
 http://www.tinkerkit.com/hall/ 
  
 created on 7 Dec 2010
 by Davide Gomba 
 modified on Dec 2011
 by Federico Vanzati
 modified on Jun 2013
 by Matteo Loglio

 This example code is in the public domain.
 */

// include the TinkerKit library
#include <TinkerKit.h>

TKHallSensor hs(I0);	// creating the object 'hs' that belongs to the 'TKHallSensor' class 
                        // and giving the value to the desired input pin

TKLed led(O0);		// creating the object 'led' that belongs to the 'TKLed' class 
			// and giving the value to the desired output pin

void setup()
{
  // initialize serial communications at 9600 bps
  Serial.begin(9600);
}

void loop()
{
  // Read the analog value of the Hall Sensor and print on the serial monitor
  Serial.print("Hall Sensor Value = ");                      
  Serial.println(hs.read());

  // with polarity() we can know if the magnetic field 
  // is going to NORTH or SOUTH without read the analog value
  if (hs.polarity() == NORTH) {
    led.on();
  }
  if (hs.polarity() == SOUTH) {
    led.off();
  }

  // wait 10 milliseconds before the next loop:
  delay(10);  
}


