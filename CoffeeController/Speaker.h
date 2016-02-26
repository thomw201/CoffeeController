#pragma once
#include "LED.h"

class Speaker
{
public:
	Speaker(int GpioPin);
	~Speaker();
	void playReadytune();
	void test();
	void playStartTune(LED led);
	void playStopTune();
	void playErrorTune(LED led);
	void playOpenTune();
	void playClosedTune(LED led);
	void speakerEnabled(bool onoff);
	bool getSpeakerStatus();
private:
	int speakerPin;
	bool speakerIsEnabled;
};

