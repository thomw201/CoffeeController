#include <iostream>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include "Speaker.h"
#include "RF.h"
#include "DistanceSensor.h"
#include "Database.h"
#include "dateTime.h"
#include "LED.h"
#include "TempSensor.h"
#include "Server.h"
using namespace std;

Speaker speaker(16);
RF rf(15);
DistanceSensor distanceSensor(4, 5);
Database db;
dateTime datetime;
LED led(1, 0, 2);
TempSensor temp(6);
Server server;
vector<int> todaysProfiles;
int updateThreadInterval = 250;
int mainThreadInterval = 500;
bool deviceOpen;
int latestTemperature;
int status = 0;

void loadProfiles() {
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

void process(string msg)
{
	cout << "processing " + msg << endl;
	string codestring = msg.substr(0, 4);
	int code = atoi(codestring.c_str());
	switch (code)
	{
	case 2000: //android connected
		led.setColor('Y');
		break;
	case 2101: //request profiles
		server.reply("2101" + db.getProfileData());
		break;
	case 2102: // update profile
		db.updateProfile(msg);
		loadProfiles();
		break;
	case 2103: // remove profile
		db.deleteProfile(msg);
		loadProfiles();
		break;
	case 2104: // new profile
		db.addProfile(msg);
		loadProfiles();
		break;
	case 2201: // logs request
		server.reply("2201" + db.getLogs());
		break;
	case 2302: //switch sound
		if (msg.at(4) == 'T')
		{
			speaker.speakerEnabled(true);
		}
		else
			speaker.speakerEnabled(false);
		break;
	case 2303:
		led.setColor(msg[4]);
		break;
	case 2304:
		led.LEDsOff();
		break;
	case 2401: //request todays profiles
	{
		string overviewString = "2401";
		ostringstream oss;
		for (size_t i = 0; i < todaysProfiles.size(); i++)
		{
			overviewString += db.getTodaysProfileNames().at(i) + ',';
			oss << db.getTodaysProfileTimes().at(i);
			overviewString += oss.str() + ',';
			oss.str("");
			oss.clear();
		}
		server.reply(overviewString);
	}
	break;
	case 2402: // request system time, status & temperature
	{
		string replyMsg = "2402";
		ostringstream oss;
		replyMsg += datetime.getTimeString() + ',';
		oss << status;
		replyMsg += oss.str() + ',';
		oss.str("");
		oss.clear();
		oss << temp.getTemp();
		replyMsg += oss.str() + ',';
		server.reply(replyMsg);
	}
		break;
	case 2301: // settings request
		string temp = "2301";
		if (speaker.getSpeakerStatus()) {
			temp += "true";
		}
		else
			temp += "false";
		//convert interval integers to strings
		ostringstream oss;
		ostringstream oss2;
		string updateThreadIntervalString;
		string mainThreadIntervalString;
		oss << updateThreadInterval;
		updateThreadIntervalString = oss.str();
		oss2 << mainThreadInterval;
		mainThreadIntervalString = oss2.str();
		server.reply(temp + ',' + updateThreadIntervalString + ',' + mainThreadIntervalString + ',');
		break;
	}
}

PI_THREAD(update)
{
	while (true)
	{
		datetime.updateTime();
		//distanceSensor.updateDistance();
		temp.read_dht11_dat();
		//cout << "Time = " << datetime.getTimeString() << "Dist = " << distanceSensor.getDistance() << "Temp = " << temp.getTemp() << endl;
		delay(updateThreadInterval);
	}
}

PI_THREAD(listen)
{
	while (true)
	{
		if (server.isConnected())
		{
			string receivedMsg = server.Listen();
			process(receivedMsg);
		}
		else
		{
			led.LEDsOff();
			server.restart();
		}

	}
}

bool switchOn(int stayontime)
{
	if (!distanceSensor.deviceIsOpen())
	{
		status = 1;
		speaker.playStartTune(led);
		rf.switchOn();
		led.setColor('B');
		cout << "Started making coffee" << endl;
		db.writeLog(1, "Started making coffee.", 0, 0, 0, 0, speaker.getSpeakerStatus());
		//wait untill the pot is warmed up till xx degrees before counting down the "stayontime"
		latestTemperature = 0;
		while (latestTemperature < 40)
		{
			latestTemperature = temp.getTemp();
			//cout << latestTemperature << endl;
			delay(5000); // check temp every 5s
		}
		status = 2;
		cout << "Keeping the coffee warm for " << stayontime << " minutes." << endl;
		led.LEDsOff();
		led.setColor('G');
		for (size_t i = 0; i < stayontime; i++)
		{
			delay(60000);
			//temp.read_dht11_dat();
		}
		db.writeLog(1, "Switching off", 0, 0, 0, 0, speaker.getSpeakerStatus());
		rf.switchOff();
		led.LEDsOff();
		status = 0;
		return true;
	}
	cout << "Could not start because the machine is opened." << endl;
	db.writeLog(3, "Could not start because the machine is opened.", 0, 0, 0, 0, speaker.getSpeakerStatus());
	speaker.playErrorTune(led);
	return false;
}

bool init() {
	// load wiringPi
	if (wiringPiSetup() == -1)
	{
		printf("WiringPi setup failed.");
		db.writeLog(3, "WiringPi setup failed.", 0, 0, 0, 0, speaker.getSpeakerStatus());
		return false;
	}
	//create listen and update threads
	int x = 0;
	x += piThreadCreate(update);
	x += piThreadCreate(listen);
	if (x != 0) {
		printf("Error starting thread.");
		db.writeLog(3, "Error starting thread.", 0, 0, 0, 0, speaker.getSpeakerStatus());
		return false;
	}
	delay(200);
	//load today's profiles at startup
	loadProfiles();
	db.writeLog(1, todaysProfiles.size() + " profiles loaded.", 0, 0, 0, 0, speaker.getSpeakerStatus());
	return true;
}

int main(int argc, char *argv[])
{
	if (!init()) {
		speaker.playErrorTune(led);
		db.writeLog(3, "Failed to initalize, exitting...", 0, 0, 0, 0, speaker.getSpeakerStatus());
		cout << "Failed to initalize, exitting..." << endl;
		exit(0);
	}
	speaker.playReadytune();
	db.writeLog(1, "Succesfully started on " + datetime.getTimeString(), 0, 0, 0, 0, speaker.getSpeakerStatus());
	while (true)
	{
		temp.read_dht11_dat();
		for (size_t i = 0; i < todaysProfiles.size(); i++)
		{
			if (datetime.compareTime(db.getTodaysProfileTimes().at(i)))
			{
				switchOn(db.getStayOnTime(todaysProfiles.at(i)));
			}
		}
		//if device is open
		if (distanceSensor.deviceIsOpen())
		{
			if (!deviceOpen)
			{
				cout << "device opened" << endl;
				led.LEDsOff();
				speaker.playOpenTune();
				deviceOpen = true;
			}
		}
		else if (deviceOpen)
		{
			speaker.playClosedTune(led);
			deviceOpen = false;
		}
		//midnight check
		delay(mainThreadInterval);
	}
	return 0;
}
