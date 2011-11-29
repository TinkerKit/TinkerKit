/*
  Button

 Turns on and off a T010111 LED Module connected to O0 (digital pin 11),
 when pressing a T000180 pushbutton attached to I0 (analog pin 0).

 This example code is in the public domain.

 based on  http://www.arduino.cc/en/Tutorial/Button
 */

// include the TinkerKit library
#include <TinkerKit.h>

// create one button object and initialize the pin on which is connected
TKButton button(I0);
// create one LED object and initialize the pin on which is connected
TKLed led(O0);

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status


void setup() {
// you don't need to configure the pins because they are already configured
// when you create the object and assign to it the pin.
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = button.state();

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {    
    // turn LED on:    
    led.on(); 
  }
  else {
    // turn LED off:
    led.off();
  }
}
