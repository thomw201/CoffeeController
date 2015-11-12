#pragma once
class Speaker
{
public:
	Speaker(int GpioPin);
	~Speaker();
	void playReadytune();
	void test();
	void playStartTune();
	void playStopTune();
	void playErrorTune();
	void speakerEnabled(bool onoff);
	bool getSpeakerStatus();
private:
	int speakerPin;
	bool speakerIsEnabled;
};

