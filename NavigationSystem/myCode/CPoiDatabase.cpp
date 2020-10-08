/*
 * CPoiDatabase.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: Tishan
 */
#include <iostream>
#include <string>

#include "CPoiDatabase.h"
#include "CPOI.h"
using namespace std;



CPoiDatabase::CPoiDatabase(){
//constructor
	this->m_noPoi = 0;
}

void CPoiDatabase::addPoi(t_poi type, string name, string description, double latitude, double longitude){
/* this method adds POI objects up to the private CPOI[10] object array's limit
*/
	if(this->m_noPoi < 10){
		m_POI[this->m_noPoi] = CPOI(type, name, description, latitude, longitude);
		this->m_noPoi++;
	} else {
		cout << "max limit of database reached." << endl;
	}
}

CPOI* CPoiDatabase::getPointerToPoi(string name){
/* returns a pointer the matching POI object from the database.
 * if the matching POI does not exist, it returns a NULL and
 * shows a warning
*/
	string mPoiName, description;
	t_poi type;
	double latitude, longitude;

	for(int i = 0; i <= this->m_noPoi ;i++ ){
		this->m_POI[i].getAllDataByReference(mPoiName, latitude, longitude, &type, description);
		if(mPoiName == name){
			return &this->m_POI[i];
		}
	}
	cout <<"ERROR: could not find POI. Something not in the pool"<<endl;
	return NULL;
}

