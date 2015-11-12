#include <iostream>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "Speaker.h"
#include "RF.h"
using namespace std;

Speaker speaker(16);
RF rf(15);

bool init() {
	// load wiringPi
	if (wiringPiSetup() == -1)
	{
		printf("WiringPi setup failed.");
		return false;
	}
	return true;
}

int main(int argc, char *argv[])
{
	if (!init()) {
		speaker.playErrorTune();
		exit(0);
	}
	speaker.playStopTune();
	delay(50);
	rf.switchOn();
	for (size_t i = 0; i < 5; i++)
	{
		delay(500);
	}
	rf.switchOff();
	cout << "hello" << endl;
	return 0;
}