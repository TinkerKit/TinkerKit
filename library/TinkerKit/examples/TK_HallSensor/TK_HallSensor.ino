#include <TinkerKit.h>

TKHallSensor hs(I0);
TKLed led(O0);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("Magnetic field distance: ");
  Serial.println(hs.get());

  if(hs.state())
    led.on();
  else
    led.off();

  delay(1000);
}


