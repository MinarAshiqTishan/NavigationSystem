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


CRoute::CRoute(unsigned int maxWp, unsigned int maxPoi){
//constructor

	//initializing everyting
	this->m_maxWp = maxWp;
	this->m_maxPoi = maxPoi;
	this->m_pWaypoint = NULL;
	this->m_pPoiDatabase = NULL;
	this->m_pPoi = NULL;
	this->m_nextWp = 0;
	this->m_nextPoi = 0;

	//dynamically allocate new memories
	this->m_pWaypoint = new CWaypoint[m_maxWp];
	this->m_pPoi = new CPOI*[m_maxPoi];


	//initializing the pointers to NULL
	for(unsigned int i = 0; i<m_maxPoi; i++){
		this->m_pPoi[i] = NULL;
	}
}


CRoute::CRoute(const CRoute& origin){
//copy constructor

	//initializing everything
	string name= "non",description="non";
	double latitude=0, longitude=0;
	t_poi temp = RESTAURANT;
	t_poi* type;
	type = &temp; //reason to iniitialize: *type having NULL value causes
	              //crash in allocating new CPOI;

	this->m_maxWp = origin.m_maxWp ;
	this->m_maxPoi = origin.m_maxPoi ;
	this->m_pPoiDatabase = origin.m_pPoiDatabase;
	this->m_nextPoi = origin.m_nextPoi ;
	this->m_nextWp = origin.m_nextWp;

	this->m_pWaypoint = new CWaypoint[m_maxWp];
	this->m_pPoi = new CPOI*[m_maxPoi];



	//copying the values from the origin object to the new objects memory

	for(unsigned int i = 0; i < m_maxWp; i++){
		origin.m_pWaypoint[i].getAllDataByReference(name,latitude,longitude);
		this->m_pWaypoint[i].set(name,latitude,longitude) ;
	}
	for(unsigned int i = 0; i < m_maxPoi; i++){
		if(origin.m_pPoi[i] != NULL){
			origin.m_pPoi[i]->getAllDataByReference(name , latitude, longitude,type,description);
		}

		this->m_pPoi[i] =  new CPOI(*type, name, description, latitude, longitude);
	}
}


CRoute::~CRoute(){
//destructor method
	delete[] this->m_pWaypoint;
    delete[] this->m_pPoi;
}


void CRoute::connectToPoiDatabase(CPoiDatabase* pPoiDB){
/* this method connects an external POI database to the
 * CRoute object's internal database pointer
 */
	this->m_pPoiDatabase = pPoiDB;
}


void CRoute::addWaypoint(const CWaypoint& wp){
/* adds CWaypoint objects to CRoute
 * */
    if(this->m_nextWp < this->m_maxWp){
		this->m_pWaypoint[this->m_nextWp] = wp;
		this->m_nextWp++;
	}else{
		cout << "maxWp reached. can't add more Waypoints" << endl;
	}
}




void CRoute::addPoi(string namePoi){
/* this method adds matching POI object from the
 * connected database to the attribute of the CRoute object
 * if the database is empty, it shows an error message
 * */
	if(this->m_pPoiDatabase == NULL){
		cout << "ERROR: not connected to database or database is empty"<<endl;
		return;
	}
	if(this->m_nextPoi < this->m_maxPoi){
			this->m_pPoi[this->m_nextPoi] = this->m_pPoiDatabase->getPointerToPoi(namePoi);
			this->m_nextPoi++;
		}else{
			cout << "maxPoi reached. can't add more POI" << endl;
		}
}

double CRoute::getDistanceNextPoi(const CWaypoint& wp, CPOI& poi){
// calculates the distance between given waypoint and next nearest poi
	CPOI nearestPoiObj;
	double dist = 0, tempDist = 0;


	if(this->m_pPoi[0] == NULL){
		return 0;
	}

	//distance from the first POI to start comparing
	poi = *this->m_pPoi[0];
	dist = poi.calculateDistance(wp);


	for(unsigned int i = 0 ; i < this->m_nextPoi ; i++){
	//loops through the m_pPoi and compares the distances
	//to find the closest one

		if(this->m_pPoi[i] == NULL) break;

		nearestPoiObj = *this->m_pPoi[i];
		tempDist = nearestPoiObj.calculateDistance(wp);

		if(dist > tempDist){
			dist = tempDist;
			poi = nearestPoiObj;
		}

	}

	return dist;

}

void CRoute::print(){
/* Prints every Waypoints and Points of interest in the Route
 * */

	cout<<"Our Route has " << this->m_nextWp << " Waypoints and " << this->m_nextPoi << " Points of Interests"<< endl;

	for(unsigned i=0; i<this->m_nextWp; i++){
			this->m_pWaypoint[i].print(MMSS);
	}

	for(unsigned i=0; i<this->m_nextPoi; i++){
		if(this->m_pPoi[i] != NULL){

			this->m_pPoi[i]->print();
		}
		else
			cout <<"No POI to print" <<endl;
	}



}













