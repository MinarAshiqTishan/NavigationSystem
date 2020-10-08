/*
 * CPoiDatabase.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: Tishan
 */
#include <iostream>
#include <string>
#include<algorithm>

#include "CPoiDatabase.h"
#include "CPOI.h"

using namespace std;



CPoiDatabase::CPoiDatabase(){
//constructor

}

void CPoiDatabase::addPoi(const CPOI& poi){
/* this method adds POI objects
*/

	m_POI.insert( make_pair(poi.getName(),poi) );

}

CPOI* CPoiDatabase::getPointerToPoi(string name){
/* returns a pointer the matching POI object from the database.
 * if the matching POI does not exist, it returns a NULL and
 * shows a warning
*/
	map<string,CPOI>::iterator itr =  m_POI.find(name);
	if (itr != m_POI.end()){
	//	cout<<"get pointer poi "<<&((*itr).second)<<endl;
		return &((*itr).second);
	}



	cout <<"ERROR: could not find POI.'"<<name<<"' not in the pool"<<endl;
	return NULL;
}
void CPoiDatabase::print(){
	for(map<string,CPOI>::iterator itr =  m_POI.begin();itr!=m_POI.end();++itr){
		cout<<(*itr).second<<endl;
		//cout<<&((*itr).second)<<endl;//<-address of the object
	}
}

const map<string, CPOI>& CPoiDatabase::getDB() const{
	return m_POI;
}

void CPoiDatabase::clearDatabase(void){
	this->m_POI.clear();
}
