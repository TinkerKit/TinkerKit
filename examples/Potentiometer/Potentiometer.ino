/*
 Read the value of a T000140 Potentiometer connected to I0, 
 then uses the results to write the brightness on a T010111 
 LED Module connected on O0. Also prints the values 
 on the serial monitor.

 created 29 Dec. 2008
 Modified 4 Sep 2010
 by Tom Igoe
 modified 7 dec 2010
 by Davide Gomba
 modified on Ded 2011
 by Federico Vanzati
 modified on Jun 2013
 by Matteo Loglio<http://matlo.me>

 This example code is in the public domain.
 */

#include <TinkerKit.h>

TKPotentiometer pot(I0);// creating the object 'pot' that belongs to the 'TKPotentiometer' 
                        // class. Hooked up on I0

TKLed led(O0);		// creating the object 'led' that belongs to the 'TKLed' class 
                        // and giving the value to the desired output pin

int brightnessVal = 0;  // value read from the pot

void setup() {
  // initialize serial communications at 9600 bps
  Serial.begin(9600);
}

void loop() {
  // read the potentiometer's value:
  brightnessVal = pot.read();            

  // set the led brightness
  led.brightness(brightnessVal);       

  // print the results to the serial monitor:
  Serial.print("brightness = " );                      
  Serial.println(brightnessVal);      


  // wait 10 milliseconds before the next loop
  delay(10);                    
}
