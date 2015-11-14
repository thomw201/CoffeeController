#pragma once
#include <sqlite3.h>
class Database
{
public:
	Database();
	~Database();
	void writeLog(int logType, char* logMessage, int logWater, int logTemp, int logLED1, int logLED2, bool logSoundStatus);
private:
	sqlite3 *db;
	bool open();
};

