#pragma once
class LED
{
public:
	LED(int Rpin, int Gpin, int Bpin);
	~LED();
	void Blink();
private:
	bool ledIsEnabled;
	int rpin, gpin, bpin;
};

