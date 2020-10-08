/*
 * CRoute.h
 *
 *  Created on: Oct 23, 2017
 *      Author: Tishan
 */

#ifndef CROUTE_H_
#define CROUTE_H_

#include <string>

#include "CWaypoint.h"
#include "CPOI.h"
#include "CPoiDatabase.h"

using namespace std;

class CRoute{
private:
	//pointer to one or an array of CWaypoint object
	CWaypoint* m_pWaypoint;

	//maximum waypoints the CRoute object can have
	unsigned int m_maxWp;

	//index to add in the next CWaypoint object
	unsigned int m_nextWp;

	//pointer to an array of CPOI*
	CPOI** m_pPoi;

	//maximum number of POI a CRoute object can have
	unsigned int m_maxPoi;

	//index to add in the next CPOI object
	unsigned int  m_nextPoi;

	//pointer to an external database
	CPoiDatabase* m_pPoiDatabase;

public:
	/*Constructor*/
	CRoute(unsigned int maxWp = 0, unsigned int maxPoi = 0);
	/*Copy Constructor*/
	CRoute(const CRoute& origin); //parameter: reference to a const CRoute object
	/*Destructor*/
	~CRoute();

	//Connect m_pPoiDatabase to an external database
	void connectToPoiDatabase(CPoiDatabase* pPoiDB);

	//Adds CWaypoint objects in m_pWaypoint
	void addWaypoint(const CWaypoint& wp); //parameter: reference to a const CWaypoint object

	//finds the matching POI in the poidatabase and adds it to m_pPoi
	void addPoi(string namePoi);

	//gets the distance between an waypoint and POI
	double getDistanceNextPoi(const CWaypoint& wp, CPOI& poi);

	//prints the number of waypoints and POIs and their values
	void print();
};



#endif /* CROUTE_H_ */
