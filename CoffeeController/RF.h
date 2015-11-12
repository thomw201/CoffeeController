#pragma once
class RF
{
public:
	RF(int GpioPin);
	~RF();
	void switchOn();
	void switchOff();
private:
	int rfPin;
	void sendSignal(unsigned long signal, unsigned short rfPin);
};