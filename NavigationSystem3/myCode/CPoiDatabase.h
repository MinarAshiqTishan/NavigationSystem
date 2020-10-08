/*
 * CPoiDatabase.h
 *
 *  Created on: Dec 23, 2017
 *      Author: Tishan
 */

#ifndef CPOIDATABASE_H_
#define CPOIDATABASE_H_



#include <iostream>
#include <string>
#include <map>
#include "CPOI.h"
#include "CDatabase.h"
using namespace std;

class CPoiDatabase : CDatabase<CPOI>{

public:
	//Constructor
	CPoiDatabase();

	//creates a CPOI object from parameters and adds it to the database
	void addPoi(const CPOI& poi);

	//returns a pointer to the matching POI in the database
	CPOI* getPointerToPoi(string name);
	const map<string,CPOI>& getDB()const;
	void clearDatabase(void);
	void print();
};


#endif /* CPOIDATABASE_H_ */
