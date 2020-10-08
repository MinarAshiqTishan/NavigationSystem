/*
 * CNavigationSystem.h
 *
 *  Created on: Oct 23, 2017
 *      Author: Tishan
 */

#ifndef CNAVIGATIONSYSTEM_H_
#define CNAVIGATIONSYSTEM_H_

#include<iostream>
#include<fstream>
using namespace std;

#include "CPersistentStorage.h"

#include "CGPSSensor.h"
#include "CRoute.h"
#include "CPoiDatabase.h"
#include "CWpDatabase.h"


#define WRITE 1
#define READ 2
#define DELIM 3
#define TYPE 4
#define NAME 5
#define DESC 6
#define DIGIT 7
#define LAT 8
#define LON 9
#define LATR 10
#define LONR 11

class CNavigationSystem:public CPersistentStorage{
private:
	fstream wpStorage;
	fstream poiStorage;
	string wpName;
	string poiName;

	//to get the current position
	CGPSSensor m_GPSSensor;

	//for creating the whole route with waypoints and POIs
	CRoute m_route;

	//holds the POIs and acts as the external database to the route
	CPoiDatabase m_PoiDatabase;
	CWpDatabase m_WpDatabase;
	//the creation of route and database is tested here
	void enterRoute();

	//this prints the whole Route
	void printRoute();

	void printError(int errorNo,string objName, int lineNo);

	void trim(string& obj);

public:

	//Constructor
	CNavigationSystem();

	void setMediaName(string name) ;

	bool writeData (const CWpDatabase& waypointDb,
				const CPoiDatabase& poiDb) ;// read from db write to file

	bool readData (CWpDatabase& waypointDb, CPoiDatabase& poiDb,
				MergeMode mode) ;//reads from file writes to db

	//runs the testcases
	void run();
};



#endif /* CNAVIGATIONSYSTEM_H_ */
