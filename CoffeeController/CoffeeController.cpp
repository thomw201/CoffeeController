#include <iostream>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "Speaker.h"
using namespace std;

Speaker speaker(16);

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
	speaker.playReadytune();
	cout << "hello" << endl;
	return 0;
}