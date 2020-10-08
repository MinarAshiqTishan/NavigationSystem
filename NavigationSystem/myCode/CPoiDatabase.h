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

using namespace std;

class CPoiDatabase{
private:
	//array of CPOI objects that acts as the container for the database
	CPOI m_POI[10];

	//index for m_POI. If 0 then the database is empty. Maximum value 10
	int m_noPoi;

public:
	//Constructor
	CPoiDatabase();

	//creates a CPOI object from parameters and adds it to the database
	void addPoi(t_poi type, string name, string description, double latitude, double longitude);

	//returns a pointer to the matching POI in the database
	CPOI* getPointerToPoi(string name);
};


#endif /* CPOIDATABASE_H_ */
