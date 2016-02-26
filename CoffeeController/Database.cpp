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

bool Database::open() {
	int rc;
	/* Open database */
	//rc = sqlite3_open("RaspiCoffeeDB.db", &db);
	rc = sqlite3_open("/home/pi/CoffeeController/CoffeeController/CoffeeController/RaspiCoffeeDB.db", &db);
	if (rc) {
		return false;
	}
}

vector<string> Database::getTodaysProfileNames() {
	return profileNames;
}

vector<int> Database::getTodaysProfileTimes() {
	return profileTimes;
}

void Database::addProfile(string profileData)
{
	vector<string> profileVars = decodeMessage(profileData); // decode the string from var,var2 to list
	vector<string> dayVector = decodeDays(profileVars.at(4));
	string query = "INSERT INTO Days (Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday, Everyday) VALUES (";
	for (int i = 0; i < dayVector.size() - 1; i++)
	{
		query += "'" + dayVector.at(i) + "',"; //add each day variable to the query
	}
	query += "'" + dayVector.at(7) + "');"; //finish up
	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt); //execute query
	sqlite3_finalize(stmt); 
	//get the ID of the inserted days to link to the profile
	query = "SELECT MAX(ID) FROM Days";
	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	string daysID = (string((const char*)sqlite3_column_text(stmt, 0)));
	sqlite3_finalize(stmt); //execute query
	//create the profile
	query = "INSERT INTO Profiles (Name, DaysID, Starttime, Stayonfor, Active) VALUES ('" + profileVars.at(0) + "','" + daysID + "','" + profileVars.at(1) + "','" + profileVars.at(2) + "','" + profileVars.at(3) + "');";
	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt); //execute query
}

void Database::updateProfile(string updateData)
{
	vector<string> updateInfo = decodeMessage(updateData); // decode the string from var,var2 to list
	updateDays(updateInfo.at(0), updateInfo.at(5));
	string query = "UPDATE Profiles SET Name='" + updateInfo.at(1) + "', Starttime='" + updateInfo.at(2) + "', Stayonfor='" + updateInfo.at(3) + "', Active='" + updateInfo.at(4) + "' WHERE ID=" + updateInfo.at(0) + ";";
	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void Database::updateDays(string ID, string days)
{
	string query = "SELECT DaysID FROM Profiles WHERE ID =" + ID + ";"; 
	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	string daysID = (string((const char*)sqlite3_column_text(stmt, 0)));
	cout << "DayID: " + daysID << endl;
	sqlite3_finalize(stmt);
	vector<string> dayVector = decodeDays(days);
	string query2 = "UPDATE Days SET Monday ='" + dayVector.at(0) + "',Tuesday='" + dayVector.at(1) + "', Wednesday='" + dayVector.at(2) + "', Thursday='" + dayVector.at(3) + "', Friday='" + dayVector.at(4) + "', Saturday='" + dayVector.at(5) + "', Sunday='" + dayVector.at(6) + "', Everyday='" + dayVector.at(7) + "' where ID ='" + daysID + "';";
	sqlite3_prepare(db, query2.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void Database::deleteProfile(string profileID)
{
	string query = "DELETE FROM Profiles WHERE ID = " + profileID.substr(4, profileID.length()) + ";";
	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

string Database::getProfileData()
{
	string profileData = "";
	//string profileIDs = "";
	sqlite3_prepare(db, "select * from profiles INNER JOIN days where days.id = profiles.DaysID;", -1, &stmt, NULL);
	sqlite3_step(stmt);
	while (sqlite3_column_int(stmt, 0))
	{
		profileData += (string((const char*)sqlite3_column_text(stmt, 0))) + ',';
		profileData += (string((const char*)sqlite3_column_text(stmt, 1))) + ',';
		profileData += (string((const char*)sqlite3_column_text(stmt, 3))) + ',';
		profileData += (string((const char*)sqlite3_column_text(stmt, 4))) + ',';
		profileData += (string((const char*)sqlite3_column_text(stmt, 5))) + ',';
		for (int i = 7; i < 15; i++)
		{
			profileData += (string((const char*)sqlite3_column_text(stmt, i)));
		}
		profileData += ',';
		sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	return profileData;
}

int Database::getStayOnTime(int id) {
	sqlite3_prepare(db, "SELECT Stayonfor FROM Profiles WHERE ID = ?", -1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, id);
	sqlite3_step(stmt);
	int Stayontime = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	return Stayontime;
}

vector<string> Database::decodeMessage(string message)
{
	vector<string> storedStrings;
	string temp = "";
	for (int i = 4; i < message.size(); i++)
	{
		//while it doesnt hit the end of the id data string
		if (message[i] != ',') //while it does not hit the end of the number, profilename etc
		{
			temp += message[i];
		}
		else {
			storedStrings.push_back(temp);
			temp = "";
		}
		
	}
	storedStrings.push_back(temp);
	return storedStrings;
}

vector<string> Database::decodeDays(string days)
{
	vector<string> dayVector;
	for (int i = 0; i < days.size(); i++) //prepare the days from binary string to vector to make the query possible
	{
		string temp = "";
		temp += days[i];
		dayVector.push_back(temp);
	}
	return dayVector;
}

vector<int> Database::getProfilesByDay(string day) {
	//clear the vector before writing new query results into it
	profileIDs.clear();
	profileNames.clear();
	profileTimes.clear();
	//create statement string
	string query = "select * from Profiles INNER JOIN Days ON Profiles.DaysID == Days.ID WHERE (" + day + "== 1 OR Everyday == 1) and Profiles.Active == 1";
	//prepare sql statement
	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	//run statement
	sqlite3_step(stmt);
	while (sqlite3_column_int(stmt, 0))
	{
		profileIDs.push_back(sqlite3_column_int(stmt, 0));
		//cache profilenames/times for later use
		profileNames.push_back(string((const char*)sqlite3_column_text(stmt, 1)));
		profileTimes.push_back(sqlite3_column_int(stmt, 3));
		sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	//sqlite3_close(db);
	return profileIDs;
}
//builds and returns the logs in string format - sep=, - end=;
string Database::getLogs()
{
	string logString = "";
	int count = 0;
	string query =  "select * from Log order by ID DESC";
	//prepare sql statement
	sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
	//run statement
	sqlite3_step(stmt);
	while (sqlite3_column_int(stmt, 0) && count < 15)
	{
		logString += string((const char*)sqlite3_column_text(stmt, 0)) + ','; // log id
		logString += string((const char*)sqlite3_column_text(stmt, 1)) + ','; // log time
		logString += string((const char*)sqlite3_column_text(stmt, 2)) + ','; //log type
		logString += string((const char*)sqlite3_column_text(stmt, 3)) + ','; //log message + end
		sqlite3_step(stmt);
		count++;
	}
	return logString;
}

/* writes a log message into the db - logtype:(1: Info, 2: Warning, 3: Error, 4: Debug) - Message, Water: Water level - LED1: RGB values - LED2 RGB Values - SoundStatus: 1=on 0=off*/
void Database::writeLog(int logType, string logMessage, int logWater, int logTemp, int logLED1, int logLED2, bool logSoundStatus) {
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