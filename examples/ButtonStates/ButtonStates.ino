/*
  Test the different Button methods: pressed, released, held
  and getSwitch. 
  
  modified in by Matteo Loglio on 6/7/13
*/

#include <TinkerKit.h>

TKButton btn(I0);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if(btn.pressed())
    Serial.println("pressed"); 
  if(btn.held())
    Serial.println("held"); 
  if(btn.released()) {
    Serial.println("released"); 
    Serial.print("switch: ");
    Serial.println(btn.getSwitch());
  }

  delay(50);  
}



