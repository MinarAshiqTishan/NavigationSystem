/*
 * CPoiDatabase.h
 *
 *  Created on: Oct 23, 2017
 *      Author: Tishan
 */

#ifndef CPOIDATABASE_H_
#define CPOIDATABASE_H_

#include <string>
#include "CPOI.h"
#include<map>

using namespace std;

class CPoiDatabase{
private:
	//array of CPOI objects that acts as the container for the database
//	CPOI m_POI[10];

	map<string,CPOI> m_POI;



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
