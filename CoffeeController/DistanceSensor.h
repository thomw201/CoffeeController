#pragma once
class DistanceSensor
{
public:
	DistanceSensor(int TRIG, int ECHO);
	~DistanceSensor();
	int getDistance();
	int ECHO, TRIG;
private:

};

