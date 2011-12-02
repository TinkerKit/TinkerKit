#include <TinkerKit.h>

TKPotentiometer pot1(I0), pot2(I1);

int val1, val2;

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	val1 = pot1.get();
	val2 = pot2.get();

	Serial.print("val1: \t");
	Serial.print(val1);
	Serial.print("\tval2: \t");
	Serial.println(val2);

	delay(1000);
}