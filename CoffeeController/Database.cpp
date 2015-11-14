#include "Database.h"
#include <stdio.h>
#include <sqlite3.h> 
using namespace std;

Database::Database()
{
	db = NULL;
	open();
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

void Database::writeLog(int logType, char* logMessage, int logWater, int logTemp, int logLED1, int logLED2, bool logSoundStatus){
	char *zErrMsg = 0;
	char *sql;
	const char insert_sql[] = "INSERT INTO Log (Type, Message, Water, Temp, LED1, LED2, Sound) VALUES (?, ?, ?, ?, ?, ?, ?)";
	sqlite3_stmt *insert_stmt = NULL;
	sqlite3_prepare_v2(db, insert_sql, -1, &insert_stmt, NULL);
	//bind parameters into query
	sqlite3_bind_int(insert_stmt, 1, logType);
	sqlite3_bind_text(insert_stmt, 2, logMessage, 50, NULL);
	sqlite3_bind_int(insert_stmt, 3, logWater);
	sqlite3_bind_int(insert_stmt, 4, logTemp);
	sqlite3_bind_int(insert_stmt, 5, logLED1);
	sqlite3_bind_int(insert_stmt, 6, logLED2);
	sqlite3_bind_int(insert_stmt, 7, logSoundStatus);
	sqlite3_step(insert_stmt);
	sqlite3_finalize(insert_stmt);
	//sqlite3_close(db);
}