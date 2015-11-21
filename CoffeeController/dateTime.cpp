#include "dateTime.h"
#include <string>
#include <iostream>
using namespace std;

time_t currentTime;
struct tm *localTime;

dateTime::dateTime()
{
}

dateTime::~dateTime()
{
}
//retrieve the OS's current date and time
void dateTime::updateTime(){
	time(&currentTime);
}
/*extracts the day from the current time and returns it as an integer (day nr since sunday)*/
int dateTime::getDay(){
	// Convert the current time to the struct
	localTime = localtime(&currentTime);  
	return localTime->tm_wday;
}
/*returns string format of the datetime*/
string dateTime::getTimeString(){
	return ctime(&currentTime);
}