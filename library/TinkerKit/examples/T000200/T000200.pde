#include <TinkerKit.h>

/*
  Analog input, analog output, serial output

 Reads an analog input pin, and T000200  Themistor Analog Sensor connected to I0, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) on a T010111 LED Module connected on O0.
 Also prints the results to the serial monitor.

 created by Tom Igoe
 modified by Davide Gomba

 This example code is in the public domain.

 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = I0;  // Analog input pin that the Themistor is attached to
const int analogOutPin= O0; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);            
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);  
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);          

  // print the results to the serial monitor:
  Serial.print("sensor = " );                      
  Serial.print(sensorValue);      
  Serial.print("\t output = ");      
  Serial.println(outputValue);  

  // wait 10 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(10);                    
}