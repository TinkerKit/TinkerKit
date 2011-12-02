#include <TinkerKit.h>

TKGyro gyro(I0, I1, TK_X4);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("X raw: ");
  Serial.print(gyro.getXAxis()); 
  Serial.print("\trate: ");
  Serial.print(gyro.xAxisRate());
  Serial.print("\t|\t Y raw: ");
  Serial.print(gyro.getYAxis());
  Serial.print("\trate: ");
  Serial.println(gyro.yAxisRate());
  
  delay(1000);
}


