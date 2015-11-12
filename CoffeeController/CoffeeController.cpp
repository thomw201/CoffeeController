#include <iostream>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "Speaker.h"
#include "RF.h"
#include "DistanceSensor.h"
using namespace std;

Speaker speaker(16);
RF rf(15);
DistanceSensor distanceSensor(4, 5);
time_t currentTime;
int currentDistance;

PI_THREAD(timer)
{
	while (true)
	{
		//currentTime = time(NULL);
		time(&currentTime);
		currentDistance = distanceSensor.getDistance();
		delay(100);
	}
}

bool init() {
	// load wiringPi
	if (wiringPiSetup() == -1)
	{
		printf("WiringPi setup failed.");
		return false;
	}
	currentDistance = 9;
	//create listen and timer threads
	int x = 0;
	x += piThreadCreate(timer);
	//x += piThreadCreate(listen);
	if (x != 0)
		return false;
	return true;
}

int main(int argc, char *argv[])
{
	if (!init()) {
		speaker.playErrorTune();
		exit(0);
	}
	speaker.playReadytune();
	delay(50);
	rf.switchOn();
	delay(50);
	while (currentDistance < 100)
	{
		delay(50);
		cout << currentDistance << endl;
	}
	speaker.playErrorTune();
	rf.switchOff();
	return 0;
}