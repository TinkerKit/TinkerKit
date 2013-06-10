/*
 Relay

 Turns on and off a Relay Module connected to O0,
 when pressing a Button Module attached to I0.
 http://www.tinkerkit.com/button/
 http://www.tinkerkit.com/relay/

 This example code is in the public domain.
 
 created in Dec 2011
 by Federico Vanzati
 modified in Jun 2013
 by Matteo Loglio<http://matlo.me>
 
 This example code is in the public domain.
 */

// include the TinkerKit library
#include <TinkerKit.h>

TKButton btn(I0);    // creating the object 'led' that belongs to the 'TKLed' class 
		     // and giving the value to the desired output pin

TKMosFet relay(O0);  // creating the object 'relay' that belongs to the 'TKRlay' class 
                     // and giving the value to the desired output pin

void setup() {
  // TinkerKit 'object' eliminate the need for pin declaration with pinMode()
}

void loop() 
{
  // check the switch state
  if(btn.readSwitch() == HIGH) {  
    relay.on();  
  }
  else{                       
    relay.off();  
  }
}

