#pragma once
class LED
{
public:
	LED(int Rpin, int Gpin, int Bpin);
	~LED();
	void Blink();
	void LEDsOff();
	void setColor(char color);
	void intToColor(int Int);
private:
	bool ledIsEnabled;
	int rpin, gpin, bpin;
};

