#pragma once
class TempSensor
{
public:
	TempSensor(int tempsensorPin);
	~TempSensor();
	int getTemp();
	void read_dht11_dat();
private:
	int tsPin, currentTemperature;
};

