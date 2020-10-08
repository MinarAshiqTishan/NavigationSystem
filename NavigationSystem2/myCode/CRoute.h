/*
 * CRoute.h
 *
 *  Created on: Oct 23, 2017
 *      Author: Tishan
 */

#ifndef CROUTE_H_
#define CROUTE_H_

#include <string>
#include<list>
#include<map>


#include "CWaypoint.h"
#include "CPOI.h"
#include "CPoiDatabase.h"
#include "CWpDatabase.h"
using namespace std;

class CRoute{
private:

	//container for the route
	list<CWaypoint*> m_route;


	//pointer to an external database
	CPoiDatabase* m_pPoiDatabase;

	//pointer to an external database
	CWpDatabase* m_pWpDatabase;

public:
	/*Constructor*/
	CRoute();
	/*Copy Constructor*/
	CRoute(const CRoute& origin); //parameter: reference to a const CRoute object
	/*Destructor*/
	~CRoute();

	//Connect  to an external database
	void connectToPoiDatabase(CPoiDatabase* pPoiDB);

	//Connect  to an external database
	void connectToWpDatabase(CWpDatabase* pWpDB);

	//Adds CWaypoint objects in m_pWaypoint
	void addWaypoint(string name); //parameter: reference to a const CWaypoint object

	//finds the matching POI in the poidatabase and adds it to m_pPoi
	void addPoi(string namePoi, string afterWp);


	//prints the number of waypoints and POIs and their values
	void print();


	CRoute operator+( const CRoute& cr2);
	CRoute& operator=(const CRoute& origin);
	CRoute& operator+=(const string name);


};



#endif /* CROUTE_H_ */
