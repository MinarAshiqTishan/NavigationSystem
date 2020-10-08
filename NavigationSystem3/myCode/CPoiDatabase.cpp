/*
 * CPoiDatabase.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: Tishan
 */
#include <iostream>
#include <string>
#include<algorithm>

#include "CDatabase.h"
#include "CPOI.h"
#include "CPoiDatabase.h"
using namespace std;



CPoiDatabase::CPoiDatabase(){
//constructor

}

void CPoiDatabase::addPoi(const CPOI& poi){
/* this method adds POI objects
*/

	CDatabase::add(poi);

}

CPOI* CPoiDatabase::getPointerToPoi(string name){
/* returns a pointer the matching POI object from the database.
 * if the matching POI does not exist, it returns a NULL and
 * shows a warning
*/

	return CDatabase::getPointerToVal(name);
}
void CPoiDatabase::print(){

	CDatabase::print();
}

const map<string, CPOI>& CPoiDatabase::getDB() const{
	return CDatabase::getDB();
}

void CPoiDatabase::clearDatabase(void){
	CDatabase::clearDatabase();
}
