#pragma once
#include <vector>
using namespace std;
class DistanceSensor
{
public:
	DistanceSensor(int TRIG, int ECHO);
	~DistanceSensor();
	void updateDistance();
	bool validateDistance();
	bool deviceIsOpen();
	int getDistance();
	void setStartDistance();
private:
	int ECHO, TRIG;
	int validatedDistance;
	int startDistance;
	vector<int> measuredDistances;
};

