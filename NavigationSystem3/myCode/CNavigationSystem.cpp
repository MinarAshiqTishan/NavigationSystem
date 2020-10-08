/*
 * CNavigationSystem.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: Tishan
 */


#include <iostream>
#include <string>
#include <stdlib.h>

#include<ios>
#include <cstdlib>
#include<algorithm>


#include "CGPSSensor.h"
#include "CRoute.h"
#include "CNavigationSystem.h"
#include "CWaypoint.h"
#include "CdbStorage.h"
#include "CDatabase.h"
#include "CPersistentStorage.h"
#include "CJsonPersistence.h"
using namespace std;




CNavigationSystem::CNavigationSystem(){}


void CNavigationSystem::run(){
	// this method runs the testcases
	enterRoute();
	printRoute();


}

void CNavigationSystem::enterRoute(){
	/*
	 * creates a Route with waypoints and Points of interests
	 */
	//CWaypoint currPos = this->m_GPSSensor.getCurrentPosition();

	CRoute cr;
	CJsonPersistence dbs;

	dbs.setMediaName("first");
	bool fileerror = dbs.readData(this->m_WpDatabase,this->m_PoiDatabase,CPersistentStorage::REPLACE);

	if(fileerror) return;

	cr.connectToWpDatabase(&this->m_WpDatabase);
	cr.connectToPoiDatabase(&this->m_PoiDatabase);

	//cout<<"\nAdding  waypoint to  cr CRoute local obj in the function\n-----------------------------"<<endl;

	cr.addWaypoint("Amsterdam");
	cr.addWaypoint("Darmstadt");


	//cout<<"\nadding stuff to cr with AddPOI\n-----------------------------"<<endl;

	cr.addPoi("Mensa HDA","Darmstadt");
	cr.addPoi("sitte","Amsterdam");

	//cout<<"\nadding in cr with +=\n-------------------------"<<endl;
	cr+="Berlin";
	//this->m_PoiDatabase.print();
	//cout<<"\nassigning cr to m_route\n-----------------------------"<<endl;
	this->m_route = cr;

	/* test of deepcopy
	  	  cout<<"-------------"<<endl;
	  	  cr+="dio";
	  	  cr.print();
	  	  cout<<"-------------"<<endl;
	 * */

	/*uncomment to check if copy constructor works
		cout<<"-------------"<<endl;
		CRoute dr(cr);
		dr+="dio";
		dr.print();
	cout<<"-------------"<<endl;
	 */

}

void CNavigationSystem::printRoute(){
	/* Prints every Waypoints and Points of interest in the Route
	 * */

	this->m_route.print();
//	vector<const CWaypoint*> vroute = this->m_route.getRoute();
//	vector<const CWaypoint*>::const_iterator itr = vroute.begin();
//	for(; itr != vroute.end(); itr++){
//		cout <<  (**itr) <<endl;
//	}
}


