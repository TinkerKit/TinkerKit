/*
 Button

 Turns on and off a T010111 LED Module connected to O0 (digital pin 11),
 when pressing a T000180 pushbutton attached to I0 (analog pin 0).

 This example code is in the public domain.

 created in Dec 2011
 by Federico Vanzati

 based on  http://www.arduino.cc/en/Tutorial/Button
 */

// include the TinkerKit library
#include <TinkerKit.h>

TKButton button(I0);	// creating the object 'button' that belongs to the 'TKButton' class 
                        // and giving the value to the desired input pin

TKLed led(O0);		// creating the object 'led' that belongs to the 'TKLed' class 
                        // and giving the value to the desired output pin


void setup() {
// TinkerKit 'object' eliminate the need for pin declaration with pinMode()
}

void loop()
{
  // check if the pushbutton is pressed.
  // if it is, the button.state() is HIGH:
  if (button.state() == HIGH) {    
    // turn LED on:    
    led.on(); 
  } else {
    // turn LED off:
    led.off();
  }
}
