/*
Increasing & Decreasing
 
 this sketch shows how to use increasing() and
 decreasing() on analog inputs. 
 
 increasing() returns HIGH when values are rising, 
 decreasing() is HIGH when values are decreasing
 
 created 1 Jul 2013
 by Matteo Loglio (matlo.me)
 
 This example code is in the public domain.
 */

// include the TinkerKit library
#include <TinkerKit.h>

TKThermistor therm(I0);       // creating the object 'therm' that belongs to the 'TKThermistor' class 
// and giving the value to the desired output pin

void setup()
{
  // initialize serial communications at 9600 bps
  Serial.begin(9600);
}

void loop()
{
  if (therm.increasing()) Serial.println("increasing");
  if (therm.decreasing()) Serial.println("decreasing");
  delay(50);
}