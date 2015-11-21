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

vector<int> Database::getProfileByDay(int day){
	//clear the vector before writing new query results into it
	IDs.clear();
	//prepare sql statement
	sqlite3_prepare(db, "SELECT ID from Profiles where DayofWeek == ? or DayofWeek == 7 AND Active == 1", -1, &stmt, NULL);
	//bind parameter into the query (the days)
	sqlite3_bind_int(stmt, 1, day);
	//run statement
	sqlite3_step(stmt);
	while (sqlite3_column_text(stmt, 0))
	{
		IDs.push_back(sqlite3_column_int(stmt, 0));
		sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	//sqlite3_close(db);
	return IDs;
}

void Database::writeLog(int logType, char* logMessage, int logWater, int logTemp, int logLED1, int logLED2, bool logSoundStatus){
	const char insert_sql[] = "INSERT INTO Log (Type, Message, Water, Temp, LED1, LED2, Sound) VALUES (?, ?, ?, ?, ?, ?, ?)";
	stmt = NULL;
	sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL);
	//bind parameters into query
	sqlite3_bind_int(stmt, 1, logType);
	sqlite3_bind_text(stmt, 2, logMessage, 50, NULL);
	sqlite3_bind_int(stmt, 3, logWater);
	sqlite3_bind_int(stmt, 4, logTemp);
	sqlite3_bind_int(stmt, 5, logLED1);
	sqlite3_bind_int(stmt, 6, logLED2);
	sqlite3_bind_int(stmt, 7, logSoundStatus);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	//sqlite3_close(db);
}