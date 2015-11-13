#include "Database.h"
#include "sqlite3.h"
#include <stdio.h>

sqlite3 *db;

Database::Database()
{
}


Database::~Database()
{
}

bool Database::insertLog(){
	if (sqlite3_open("RaspiCoffeeDB.db", &db) == SQLITE_OK){
		return true;
	}
	else
		return false;
}