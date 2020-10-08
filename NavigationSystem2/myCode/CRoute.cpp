/*
 * CRoute.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: Tishan
 *
 */


#include <iostream>
#include <string>
#include <stdlib.h>

#include "CPoiDatabase.h"
#include "CPOI.h"
#include "CRoute.h"
#include "CWaypoint.h"

using namespace std;


CRoute::CRoute(){
	//constructor

	this->m_pPoiDatabase = NULL;
	this->m_pWpDatabase = NULL;
}


CRoute::CRoute(const CRoute& origin){
	//copy constructor

	this->m_route.clear();

	this->m_pPoiDatabase = origin.m_pPoiDatabase;
	this->m_pWpDatabase = origin.m_pWpDatabase;

	for(list<CWaypoint*>::const_iterator itr = origin.m_route.begin(); itr!=origin.m_route.end();++itr){
		this->m_route.push_back(&(**itr));

	}




}


CRoute::~CRoute(){
	//destructor method

	this->m_route.clear();
}


void CRoute::connectToPoiDatabase(CPoiDatabase* pPoiDB){
	/* this method connects an external POI database to the
	 * CRoute object's internal database pointer
	 */
	this->m_pPoiDatabase = pPoiDB;
}

void CRoute::connectToWpDatabase(CWpDatabase* pWpDB){
	/* this method connects an external POI database to the
		 * CRoute object's internal database pointer
		 */
	this->m_pWpDatabase = pWpDB;
}

void CRoute::addWaypoint(string name){
	/* adds CWaypoint objects to CRoute
	 * */

	CWaypoint *wp;

	if(this->m_pWpDatabase == NULL){
		cout << "ERROR: not connected to database or database is empty"<<endl;
		return;
	}

	wp = &(*this->m_pWpDatabase->getPointerToWaypoint(name));

	if(wp!=NULL){

		this->m_route.push_back(&(*wp));

	}
}



void CRoute::addPoi(string namePoi, string afterWp){
	/* this method adds matching POI object from the
	 * connected database to the attribute of the CRoute object
	 * if the database is empty, it shows an error message
	 * */
	if(this->m_pPoiDatabase == NULL){
		cout << "ERROR: not connected to database or database is empty"<<endl;
		return;
	}


	CPOI *poi;


	poi = this->m_pPoiDatabase->getPointerToPoi(namePoi);

	if(poi == NULL)
		return;

	for(list<CWaypoint*>::reverse_iterator itr = this->m_route.rbegin(); itr != this->m_route.rend(); ++itr){
		if((*itr)->getName() == afterWp){
			this->m_route.insert(itr.base(),&(*poi));
			return;
		}

	}


	this->m_route.push_back(poi);


}



void CRoute::print(){
	/* Prints every Waypoints and Points of interest in the Route
	 * */


//	CPOI *poi;
	if(!this->m_route.empty())
		for(list<CWaypoint*>::iterator itr = this->m_route.begin();itr!= this->m_route.end();++itr){

				cout<<(**itr)<<endl;

		}

	else
		cout <<"No Route to print" <<endl;

}

CRoute& CRoute::operator =(const CRoute& origin){

	this->m_route.clear();

	this->m_pPoiDatabase = origin.m_pPoiDatabase;
	this->m_pWpDatabase = origin.m_pWpDatabase;

	for(list<CWaypoint*>::const_iterator itr = origin.m_route.begin(); itr!=origin.m_route.end();++itr){

		this->m_route.push_back(&(**itr));

	}

	return *this;

}



CRoute& CRoute::operator +=(const string name)
		{
	CWaypoint* wp = this->m_pWpDatabase->getPointerToWaypoint(name);
	if(wp != NULL)
		this->addWaypoint(wp->getName());

	CPOI* poi = this->m_pPoiDatabase->getPointerToPoi(name);
	if(poi!=NULL)
		this->m_route.push_back(&(*poi));


	return *this;
		}

CRoute CRoute::operator +(const CRoute& cr2){
	CRoute cr1;
	if(this->m_pPoiDatabase == cr2.m_pPoiDatabase && this->m_pWpDatabase == cr2.m_pWpDatabase){
		cr1.m_route.insert(cr1.m_route.end(),this->m_route.begin(),this->m_route.end());
		cr1.m_route.insert(cr1.m_route.end(),cr2.m_route.begin(),cr2.m_route.end());
	}else{
		cr1.m_route.empty();
		cout<<"ERROR: the route don't point to the same databases"<<endl;
	}

	return cr1;
}

