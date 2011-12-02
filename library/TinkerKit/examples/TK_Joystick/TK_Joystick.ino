#include <TinkerKit.h>

TKJoystick joystick(I0, I1);

void setup() 
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("X: ");
  Serial.print(joystick.getXAxis());
  
  Serial.print("\tY: ");
  Serial.println(joystick.getYAxis());
  
  delay(1000);
}


