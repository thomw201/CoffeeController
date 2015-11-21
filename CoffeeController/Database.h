#pragma once
#include <sqlite3.h>
#include <vector>
#include <string>
using namespace std;
class Database
{
public:
	Database();
	~Database();
	void writeLog(int logType, char* logMessage, int logWater, int logTemp, int logLED1, int logLED2, bool logSoundStatus);
	vector<int> getProfileByDay(int day);
private:
	sqlite3 *db;
	char *sql;
	sqlite3_stmt *stmt;
	vector<int> IDs;
	bool open();
};

