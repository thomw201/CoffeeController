#include <iostream>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Speaker.h"
#include "RF.h"
#include "DistanceSensor.h"
#include "Database.h"
#include "dateTime.h"
#include "LED.h"
using namespace std;

Speaker speaker(16);
RF rf(15);
DistanceSensor distanceSensor(4, 5);
Database db;
dateTime datetime;
LED led(1, 0, 2);

vector<int> todaysProfiles;
bool deviceOpen;

PI_THREAD(update)
{
	while (true)
	{
		datetime.updateTime();
		distanceSensor.updateDistance();
		cout << "Time = " << datetime.getTimeString() << "Dist = " << distanceSensor.getDistance() << endl;
		delay(500);
	}
}

bool switchOn(int stayontime)
{
	if (!distanceSensor.deviceIsOpen())
	{
		speaker.playStartTune(led);
		rf.switchOn();
		cout << "Started making coffee" << endl;
		db.writeLog(1, "Started making coffee.", distanceSensor.getDistance(), 0, 0, 0, speaker.getSpeakerStatus());
		delay(20000); //wait 20s
		cout << "Keeping the coffee warm for " << stayontime << " minutes." << endl;
		//while (startDistance - distanceSensor.getDistance() < -10)
		//{
		//	delay(250);
		//}
		led.LEDsOff();
		led.setColor('G');
		for (size_t i = 0; i < stayontime; i++)
		{
			delay(60000);
		}
		return true;
	}
	cout << "Could not start because the machine is opened." << endl;
	db.writeLog(3, "Could not start because the machine is opened.", distanceSensor.getDistance(), 0, 0, 0, speaker.getSpeakerStatus());
	speaker.playErrorTune(led);
	return false;
}

void loadProfiles(){
	todaysProfiles = db.getProfilesByDay(datetime.getDayString());
	for (size_t i = 0; i < todaysProfiles.size(); i++)
	{
		cout << "Loaded profile with ID; " << todaysProfiles.at(i) << "\n";
	}
	if (todaysProfiles.empty())
	{
		cout << "No profiles loaded" << endl;
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
	//load today's profiles at startup
	loadProfiles();
	db.writeLog(1, todaysProfiles.size() + " profiles loaded.", distanceSensor.getDistance(), 0, 0, 0, speaker.getSpeakerStatus());
	return true;
}

int main(int argc, char *argv[])
{
	if (!init()) {
		speaker.playErrorTune(led);
		db.writeLog(3, "Failed to initalize, exitting...", distanceSensor.getDistance(), 0, 0, 0, speaker.getSpeakerStatus());
		cout << "Failed to initalize, exitting..." << endl;
		exit(0);
	}
	speaker.playStartTune(led);
	db.writeLog(1, "Succesfully started on " + datetime.getTimeString(), distanceSensor.getDistance(), 0, 0, 0, speaker.getSpeakerStatus());

	while (true)
	{
		for (size_t i = 0; i < todaysProfiles.size(); i++)
		{
			if (datetime.compareTime(db.getProfileTimes().at(i)))
			{
				switchOn(db.getStayOnTime(todaysProfiles.at(i)));
				db.writeLog(1, "Switching off", distanceSensor.getDistance(), 0, 0, 0, speaker.getSpeakerStatus());
				rf.switchOff();
			}
		}
		if (!distanceSensor.deviceIsOpen())
		{
			led.LEDsOff();
			speaker.playStopTune();
			deviceOpen = true;
		}
		else if (!deviceOpen)
		{
			deviceOpen = false;
		}
		//midnight check
		delay(1000);
	}
	return 0;
}