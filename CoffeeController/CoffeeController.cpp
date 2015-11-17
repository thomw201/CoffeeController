#include <iostream>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "Speaker.h"
#include "RF.h"
#include "DistanceSensor.h"
#include "Database.h"
using namespace std;

Speaker speaker(16);
RF rf(15);
DistanceSensor distanceSensor(4, 5);
Database db;
time_t currentTime;
int currentDistance;
int noWater = 9;


bool switchOn()
{
	if (currentDistance < 22)
	{
		speaker.playStartTune();
		delay(100);
		rf.switchOn();
		delay(100);
		cout << "Started making coffee" << endl;
		db.writeLog(1, "Started making coffee.", distanceSensor.getDistance(), 0, 0, 0, speaker.getSpeakerStatus());
		delay(500);
		cout << "Water: " << currentDistance << endl;
		//check if coffee is done every 500ms
		while (currentDistance < 50)
		{
			cout << "Water: " << currentDistance << endl;
			delay(500);
		}
		//play ready melody-
		return true;
	}
	cout << "Could not start because the machine is opened." << endl;
	db.writeLog(3, "Could not start because the machine is opened.", distanceSensor.getDistance(), 0, 0, 0, speaker.getSpeakerStatus());
	speaker.playErrorTune();
	return false;
}

PI_THREAD(update)
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
		db.writeLog(3, "WiringPi setup failed.", distanceSensor.getDistance(), 0, 0, 0, speaker.getSpeakerStatus());
		return false;
	}
	//create listen and update threads
	int x = 0;
	x += piThreadCreate(update);
	//x += piThreadCreate(listen);
	if (x != 0){
		printf("Error starting thread.");
		db.writeLog(3, "Error starting thread.", distanceSensor.getDistance(), 0, 0, 0, speaker.getSpeakerStatus());
		return false;
	}
	delay(200);
	return true;
}

int main(int argc, char *argv[])
{
	if (!init()) {
		speaker.playErrorTune();
		db.writeLog(3, "Failed to initalize, exitting...", distanceSensor.getDistance(), 0, 0, 0, speaker.getSpeakerStatus());
		cout << "Failed to initalize, exitting..." << endl;
		exit(0);
	}
	speaker.speakerEnabled(true);
	while (true)
	{
		delay(500);
	}
	//switchOn();
	//delay(5000);
	//db.writeLog(2, "Turning off", distanceSensor.getDistance(), 0, 0, 0, speaker.getSpeakerStatus());
	//rf.switchOff();
	return 0;
}