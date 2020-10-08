/*
 * CNavigationSystem.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: Tishan
 */


#include <iostream>
#include <string>
#include <stdlib.h>

#include "CGPSSensor.h"
#include "CRoute.h"
#include "CPoiDatabase.h"
#include "CNavigationSystem.h"
#include "CWaypoint.h"

#define MAXWP 10
#define MAXPOI 10

using namespace std;




CNavigationSystem::CNavigationSystem():m_route(MAXWP,MAXPOI){
	//constructor method
	//initializes m_route
}
/*
	 * CRoute cp2(3,2);
	 * this->m_route = cp2;
	 *
	 * the value of m_route could be changed this way
	 * in the enterRoute method also.
	 * But as the compiler implicitly
	 * declares a copy assignment operator i.e '='
	 * for a class, assigning in such way causes a shallow copy
	 * to occur. Therefore both
	 * the objects' private members (m_pWaypoint and m_pPoi)
	 * end up pointing to the same allocated memory block.
	 * So deleting the allocation in one object i.e cp2 by
	 * calling the destructor, creates a dangling
	 * pointer in the other object i.e m_route and
	 * the program crashes while trying to delete the
	 * same memory block again in this object.
	 *
	 * The way to avoid is to overload our
	 * own assignment operator i.e '=' and perform a deep copy.
	 *
	 * */

void CNavigationSystem::run(){
// this method runs the testcases
	enterRoute();
	printRoute();
	printDistanceCurPosNextPoi();

}

void CNavigationSystem::enterRoute(){
// creates a Route with waypoints and Points of interests

	CWaypoint amsterdam("Amsterdam", 52.3702,4.8952); //52.3702° N, 4.8952° E
	CWaypoint darmstadt("Darmstadt", 49.8728, 8.6512); //49.8728° N, 8.6512° E
	CWaypoint berlin("Berlin",52.5200,13.4050); //52.5200° N, 13.4050° E

	//test: call with empty database
	this->m_PoiDatabase.getPointerToPoi("Mensa HDA");

	//add some POIs in the database
	this->m_PoiDatabase.addPoi(RESTAURANT,"Mensa HDA","best mensa in the world" , 10,20 );
	this->m_PoiDatabase.addPoi(RESTAURANT,"Sitte","More expensive but also good" , 11,22 );
	this->m_PoiDatabase.addPoi(RESTAURANT,"itte","More expensive but also good" , 11,22 );

	//connect the database created here with route's database
	this->m_route.connectToPoiDatabase(&this->m_PoiDatabase);

	//add some waypoints to the route
	this->m_route.addWaypoint(amsterdam);
	this->m_route.addWaypoint(darmstadt);
	this->m_route.addWaypoint(berlin);

	//add some POIs to the route
	this->m_route.addPoi("Mensa HDA");
	this->m_route.addPoi("Sitte");


}

void CNavigationSystem::printRoute(){
/* Prints every Waypoints and Points of interest in the Route
 * */
	this->m_route.print();
}

void CNavigationSystem::printDistanceCurPosNextPoi(){
/* this method gets the current position of the user
 * and calculates the distance from the closest point of interest
 * */
	CWaypoint cp(this->m_GPSSensor.getCurrentPosition());
	CPOI poi;
	double dist = 0;

	//get the distance from the nearest POI from current Position
	dist = this->m_route.getDistanceNextPoi(cp,poi);

	cout << "Distance to next POI = " << dist << endl;

	//print the details of the POI
	poi.print();

}
