/*
 Read values from the T000090 LDR Analog Sensor connected to I0, 
 then uses the result to set the brightness on a T010111 LED 
 Module connected on O0. Also prints the values on the 
 serial monitor.

 created 29 Dec. 2008
 Modified 4 Sep 2010
 by Tom Igoe
 modified 7 dec 2010
 by Davide Gomba
 modified on Ded 2011
 by Federico Vanzati
 modified Jun 2013
 by Matteo Loglio<http://matlo.me>

 This example code is in the public domain.
 */

#include <TinkerKit.h>

TKLightSensor ldr(I0);	//create the "ldr" object on port I0

TKLed led(O0);		//create the "led" object on port O0

void setup() {
  // initialize serial communications at 9600 bps
  Serial.begin(9600);
}

void loop() {
  // store the ldr values into a variable called brightnessVal
  int brightnessVal = ldr.read();            

  // set the led brightness
  led.brightness(brightnessVal);       
  
  //to have it at full brightness
  //when it's dark, uncomment this line:
  //led.brightness(1023 - brightnessVal);

  // print the results to the serial monitor:
  Serial.print("brightness = " );                      
  Serial.println(brightnessVal);      


  // wait 10 milliseconds before the next loop
  delay(10);                    
}
