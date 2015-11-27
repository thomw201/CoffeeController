#include "LED.h"
#include "wiringPi.h"

LED::LED(int Rpin, int Gpin, int Bpin)
{
	rpin = Rpin;
	gpin = Gpin;
	bpin = Bpin;
	pinMode(rpin, OUTPUT);
	pinMode(gpin, OUTPUT);
	pinMode(bpin, OUTPUT);
}


LED::~LED()
{
}

void LED::Blink(){
	digitalWrite(bpin, 1);
	delay(1000);
	digitalWrite(bpin, 0);
	digitalWrite(rpin, 1);
	delay(1000);
	digitalWrite(rpin, 0);
	digitalWrite(gpin, 1);
	delay(1000);
	digitalWrite(gpin, 0);
}