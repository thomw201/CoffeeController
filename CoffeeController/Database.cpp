#include "Database.h"
#include <iostream>
#include <stdio.h>
#include <sqlite3.h> 
#include <string>
#include <vector>
using namespace std;

Database::Database()
{
	db = NULL;
	stmt = NULL;
	if (open())
	{
		cout << "Failed to open database." << endl;
	}
}

Database::~Database()
{
}

bool Database::open(){
	int rc;
	/* Open database */
	rc = sqlite3_open("RaspiCoffeeDB.db", &db);
	if (rc){
		return false;
	}
}

vector<string> Database::getProfileNames(){
	return profileNames;
}

vector<int> Database::getProfileByDay(string day){
	//clear the vector before writing new query results into it
	profileIDs.clear();
	profileNames.clear();
	//create statement string
	string query = "select * from Profiles INNER JOIN Days ON Profiles.DaysID == Days.ID WHERE (" + day + "== 1 OR Everyday == 1) and Profiles.Active == 1";
	//prepare sql statement
	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	//run statement
	sqlite3_step(stmt);
	while (sqlite3_column_int(stmt, 0))
	{
		profileIDs.push_back(sqlite3_column_int(stmt, 0));
		//cache profilenames for later use
		profileNames.push_back(string((const char*)sqlite3_column_text(stmt, 1)));
		sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	//sqlite3_close(db);
	return profileIDs;
}


/* writes a log message into the db - logtype:(1: Info, 2: Warning, 3: Error, 4: Debug) - Message, Water: Water level - LED1: RGB values - LED2 RGB Values - SoundStatus: 1=on 0=off*/
void Database::writeLog(int logType, string logMessage, int logWater, int logTemp, int logLED1, int logLED2, bool logSoundStatus){
	const char insert_sql[] = "INSERT INTO Log (Type, Message, Water, Temp, LED1, LED2, Sound) VALUES (?, ?, ?, ?, ?, ?, ?)";
	stmt = NULL;
	sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL);
	//bind parameters into query
	sqlite3_bind_int(stmt, 1, logType);
	sqlite3_bind_text(stmt, 2, logMessage.c_str(), 50, NULL);
	sqlite3_bind_int(stmt, 3, logWater);
	sqlite3_bind_int(stmt, 4, logTemp);
	sqlite3_bind_int(stmt, 5, logLED1);
	sqlite3_bind_int(stmt, 6, logLED2);
	sqlite3_bind_int(stmt, 7, logSoundStatus);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	//sqlite3_close(db);
}