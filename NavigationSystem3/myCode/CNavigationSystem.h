/*
 * CNavigationSystem.h
 *
 *  Created on: Oct 23, 2017
 *      Author: Tishan
 */

#ifndef CNAVIGATIONSYSTEM_H_
#define CNAVIGATIONSYSTEM_H_

#include<iostream>
#include<fstream>
using namespace std;

#include "CPersistentStorage.h"

#include "CGPSSensor.h"
#include "CRoute.h"
#include "CDatabase.h"
#include "CWpDatabase.h"
#include "CPoiDatabase.h"



class CNavigationSystem{
private:

	//to get the current position
	CGPSSensor m_GPSSensor;

	//for creating the whole route with waypoints and POIs
	CRoute m_route;

	//holds the POIs and acts as the external database to the route
	CPoiDatabase m_PoiDatabase;
	CWpDatabase m_WpDatabase;
	//the creation of route and database is tested here
	void enterRoute();

	//this prints the whole Route
	void printRoute();


public:

	//Constructor
	CNavigationSystem();



	//runs the testcases
	void run();
};



#endif /* CNAVIGATIONSYSTEM_H_ */
