/*
 * CdbStorage.h
 *
 *  Created on: Dec 22, 2017
 *      Author: Tishan
 */

#ifndef CDBSTORAGE_H_
#define CDBSTORAGE_H_

#include<iostream>
#include<fstream>
using namespace std;

#include "CPersistentStorage.h"

#include "CGPSSensor.h"
#include "CRoute.h"
#include "CDatabase.h"
#include "CWpDatabase.h"
#include "CPoiDatabase.h"

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


class CdbStorage : public CPersistentStorage
{

private:
	fstream wpStorage;
	fstream poiStorage;
	string wpName;
	string poiName;
	void printError(int errorNo,string objName, int lineNo);

	void trim(string& obj);


public:
	CdbStorage();
	void setMediaName(string name) ;

	bool writeData (const CWpDatabase& waypointDb,
				const CPoiDatabase& poiDb) ;// read from db write to file

	bool readData (CWpDatabase& waypointDb, CPoiDatabase& poiDb,
				MergeMode mode) ;//reads from file writes to db


};

#endif /* CDBSTORAGE_H_ */
