#include "DistanceSensor.h"
#include "wiringPi.h"

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
	return validatedDistance;
}

bool DistanceSensor::deviceIsOpen(){
	if (validateDistance())
	{
		if (measuredDistances.at(0) > 30)
		{
			return true;
		}
		else
			return false;
	}
	return false;
}

void DistanceSensor::setStartDistance(){
	startDistance = validatedDistance;
}

bool DistanceSensor::validateDistance(){
		if (measuredDistances.at(0) == measuredDistances.at(1))
		{
			validatedDistance = measuredDistances.at(0);
			return true;
		}
	return false;
}

void DistanceSensor::updateDistance(){
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

	//Get distance in cm and insert it into the vector
	measuredDistances.insert(measuredDistances.begin(), travelTime / 58);
	//ensure there's always only 2 values in the vector as cleanup
	measuredDistances.resize(2);
	validateDistance();
}