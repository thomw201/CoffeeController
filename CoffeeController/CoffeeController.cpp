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
int noWater = 9;

bool turnOn()
{
	if (currentDistance < 10)
	{
		speaker.playStartTune();
		delay(100);
		rf.switchOn();
		delay(100);
		cout << "Started making coffee" << endl;
		//check if coffee is done every 500ms
		while (currentDistance < 9)
		{
			delay(500);
		}
		//play ready melody-
		return true;
	}
	cout << "Machine is open" << endl;
	speaker.playErrorTune();
	return false;
}

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
	//create listen and timer threads
	int x = 0;
	x += piThreadCreate(timer);
	//x += piThreadCreate(listen);
	if (x != 0){
		printf("Error starting thread.");
		return false;
	}
	delay(100);
	return true;
}

int main(int argc, char *argv[])
{
	if (!init()) {
		speaker.playErrorTune();
		cout << "init failed" << endl;
		exit(0);
	}
	turnOn();

	delay(1000);
	rf.switchOff();
	return 0;
}