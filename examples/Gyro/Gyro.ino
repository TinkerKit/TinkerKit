/*
 Reads a T000064 Gyro Module with the x-axis connected to I0 pin
 the y-axis connected to the I1 pin then prints 
 the results to the serial monitor.
 http://www.tinkerkit.com/gyroscope-4x/
   

 created on Dec 2011
 by Federico Vanzati
 modified on Jun 2013
 by Matteo Loglio <http://matlo.me>

 This example code is in the public domain.
 */

// include the TinkerKit library
#include <TinkerKit.h>

TKGyro gyro(I0, I1, TK_X4);  // creating the object 'gyro' that belongs to the 'TKGyro' class 
                       	     // and giving the values to the desired input pins
                             // using the 4x amplified module, insert the TK_4X costant.


void setup()
{
  // initialize serial communications at 9600 bps
  Serial.begin(9600);
}

void loop()
{
  Serial.print("X raw: ");
  Serial.print(gyro.readX());        // print x-axis analog value
  Serial.print("\trate: ");
  Serial.print(gyro.readXAxisRate());    // print the x-axis anguar rate in the range of -/+1500 °/s
  Serial.print("\t|\t Y raw: ");  
  Serial.print(gyro.readY());        // print x-axis analog value
  Serial.print("\trate: ");
  Serial.println(gyro.readYAxisRate());  // print the x-axis anguar rate in the range of -/+1500 °/s
  
  delay(100);
}


