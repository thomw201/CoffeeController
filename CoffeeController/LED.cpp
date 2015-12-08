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

void LED::setColor(char color){
	int ledpin;
	switch (color)
	{
	case 'R':
		ledpin = rpin;
		break;
	case 'G':
		ledpin = gpin;
		break;
	case 'B':
		ledpin = bpin;
		break;
	case 'M':
		ledpin = rpin;
		digitalWrite(bpin, 1);
		break;
	case 'Y':
		ledpin = rpin;
		digitalWrite(gpin, 1);
	case 'C':
		ledpin = bpin;
		digitalWrite(gpin, 1);
		break;
	case 'W':
		ledpin = rpin;
		digitalWrite(gpin, 1);
		digitalWrite(bpin, 1);
		break;
	}
	digitalWrite(ledpin, 1);
}

void LED::LEDsOff(){
	digitalWrite(rpin, 0);
	digitalWrite(bpin, 0);
	digitalWrite(gpin, 0);
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

void LED::intToColor(int Int){
	if (Int < 1)
	{
	}
	else if (Int < 200){
		setColor('R');
	}
	else if (Int < 500){
		setColor('B');
	}
	else
		setColor('G');
}