#include "DistanceSensor.h"
#include "wIRingPi.h"

DistanceSensor::DistanceSensor(int trig, int echo)
{
	ECHO = echo;
	TRIG = trig;
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);

	//TRIG pin must start LOW
	digitalWrite(TRIG, LOW);
	delay(30);
}


DistanceSensor::~DistanceSensor()
{
}

int DistanceSensor::getDistance(){
	//Send trig pulse
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(20);
	digitalWrite(TRIG, LOW);

	//Wait for echo start
	while (digitalRead(ECHO) == LOW);

	//Wait for echo end
	long startTime = micros();
	while (digitalRead(ECHO) == HIGH);
	long travelTime = micros() - startTime;

	//Get distance in cm
	int distance = travelTime / 58;
	delay(100);
	return distance;
}