#include "dateTime.h"
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

time_t currentTime;
struct tm *localTime;
string days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
pthread_mutex_t mutex;

dateTime::dateTime()
{
}

dateTime::~dateTime()
{
}
//retrieve the OS's current date and time
void dateTime::updateTime(){
	int rc = pthread_mutex_trylock(&mutex);
	if (rc == 0)
	{
		time(&currentTime);
		localTime = localtime(&currentTime);
	}
	else
		cout << "mutex lock failed " << rc << endl;
	pthread_mutex_unlock(&mutex);
}
/*extracts the day from the current time and returns it as an integer (day nr since sunday)*/
int dateTime::getDay(){
	// Convert the current time to the struct
	return localTime->tm_wday;
}
/*returns string format of the datetime*/
string dateTime::getTimeString(){
	string time = ctime(&currentTime);
	time.erase(std::remove(time.begin(), time.end(), '\n'), time.end());
	return time;
}

string dateTime::getDayString(){
	return days[getDay() ];
}
//compares the given time to the local time, format "hhmm"
bool dateTime::compareTime(int time){
	int currentTimeInt = localTime->tm_min + (localTime->tm_hour * 100);
	//cout << "comparing " << currentTimeInt << " with " << time << endl;
	if (currentTimeInt == time)
	{
		return true;
	}
	return false;
}