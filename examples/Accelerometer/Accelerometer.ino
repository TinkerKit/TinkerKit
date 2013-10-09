/*
 Reads two analog input pins; a T000020 Accelerometer Module with the x-axis connected to I0 pin
 the y-axis connected to the I1 pin, uses the result to set the brightness of two T010111 LED Module 
 connected on O0 and O1. Also prints the results to the serial monitor.
 http://www.tinkerkit.com/accelerometer/
 
 created on Dec 2011
 by Federico Vanzati
 modified in Jul 2013 
 by Matteo Loglio

 This example code is in the public domain.

 */

// include the TinkerKit library
#include <TinkerKit.h>

TKAccelerometer accelerometer(I0, I1);  // creating the object 'accelerometer' that belongs to the 'TKAccelerometer' class 
                                  // and giving the values to the desired input pins

//TKAccelerometer accelerometer(I0, I1, I2); //if you connected also the Z axis, you
                                             //can declare it with three pins and use
                                             //functions like readZ() and readZinG().
                       

TKLed xLed(O0), yLed(O1);         // creating the objects 'xLed' & 'yLed' that both belongs to the 'TKLed' class 
                                  // and giving the values to the desired output pins

int xAxisValue = 0;           // a variable to store theaccelerometer's x value
int yAxisValue = 0;           // a variable to store theaccelerometer's y value

void setup() 
{
  // initialize serial communications at 9600 bps
  Serial.begin(9600);
}

void loop()
{
  // read the both joystick axis values:
  xAxisValue = accelerometer.readX();  
  yAxisValue = accelerometer.readY(); 

  // set the leds brightness
  xLed.brightness(xAxisValue);
  yLed.brightness(yAxisValue);

  // print the results to the serial monitor:
  Serial.print("Accelerometer X = " );                       
  Serial.print(xAxisValue);   
  Serial.print("\t Accelerometer Y = " );                       
  Serial.print(yAxisValue);     


  // wait 10 milliseconds before the next loop
  delay(10);    
}
