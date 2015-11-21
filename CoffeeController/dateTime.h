#pragma once
#include <string>
using namespace std;
class dateTime
{
public:
	dateTime();
	~dateTime();
	void updateTime();
	string getTimeString();
	int getDay();
private:
	time_t currentTime;
};

