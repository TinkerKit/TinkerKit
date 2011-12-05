/*
  Analog input, analog output, serial output

 Reads two analog input pins; a T000030 Joystick Module Analog Sensor
 connected to I0 and I1, and uses the result to set the brightness of
 two T010111 LED Module connected on O0 and O1.
 Also prints the results to the serial monitor.

 created  7 dec 2010
 by Davide Gomba
 modified on Dec 2011
 by Federico Vanzati

 This example code is in the public domain.

 */

// include the TinkerKit library
#include <TinkerKit.h>

TKJoystick joystick(I0, I1);// creating the object 'joy' that belongs to the 'TKJoystick' class 
		  	    // and giving the value to the two desired inputs pin

TKLed led1(O0), led2(O1);   // creating the objects 'led1' and 'led2' that both belongs to the 'TKLed' class 
		   	    // and giving to each the value to the desired output pin

int xAxisValue = 0;         // value read from the Joystick's first pin
int yAxisValue = 0;         // value read from the Joystick's second pin


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the both analog in values:
  xAxisValue = joystick.getXAxis();  
  yAxisValue = joystick.getYAxis();   
  
  // change the analog out value:
  led1.brightness(xAxisValue);
  led2.brightness(yAxisValue);

  // print the results to the serial monitor:
  Serial.print("Joystick X = " );                      
  Serial.print(xAxisValue);  
  Serial.print("\t Joystick Y = " );                      
  Serial.print(yAxisValue);    

  // wait 10 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(10);                    
}
