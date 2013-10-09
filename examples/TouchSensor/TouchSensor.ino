/*
 Touch Sensor

 Turns on and off a T010111 LED Module connected to O0,
 when pressing a T000220 Touch Sensor attached to I0.
 
 http://www.tinkerkit.com/led-green-10mm/
 http://www.tinkerkit.com/touch/

 · created in Dec 2011
   by Federico Vanzati
 · modified in Jun 2013 
   by Matteo Loglio <http://matlo.me>

 This example code is in the public domain.
 */

// include the TinkerKit library
#include <TinkerKit.h>

TKTouchSensor touch(I0);// creating the object 'touch' that belongs to the 'TKTouchSensor' class 
                        // and giving the value to the desired input pin

TKLed led(O0);		// creating the object 'led' that belongs to the 'TKLed' class 
                        // and giving the value to the desired output pin


void setup() {
// TinkerKit 'object' eliminate the need for pin declaration with pinMode()
}

void loop()
{
  // check the "switch state" of the sensor
  // if it is, turns on the LED
  if (touch.readSwitch() == HIGH) {      
    led.on();     // turn LED on 
  } else {
    led.off();    // turn LED off
  }
}
