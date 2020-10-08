/*
 * CWpDatabase.h
 *
 *  Created on: Nov 30, 2017
 *      Author: Tishan
 */

#ifndef CWPDATABASE_H_
#define CWPDATABASE_H_

#include<string>
#include<map>
using namespace std;

#include "CWaypoint.h"

class CWpDatabase
{
	map<string,CWaypoint> m_wp;

public:
	CWpDatabase();
	void addWaypoint(const CWaypoint& wp);
	CWaypoint* getPointerToWaypoint(string name);
	void print();
	const map<string,CWaypoint>& getDB()const;
	void clearDatabase(void);
};

#endif /* CWPDATABASE_H_ */
