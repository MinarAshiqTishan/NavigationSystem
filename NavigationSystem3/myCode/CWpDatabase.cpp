/*
 * CWpDatabase.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: Tishan
 */
#include<iostream>
#include<string>
#include<map>
using namespace std;

#include "CWpDatabase.h"
#include "CWaypoint.h"
#include "CDatabase.h"

CWpDatabase::CWpDatabase(){

}

void CWpDatabase::addWaypoint(const CWaypoint& wp){

	CDatabase::add(wp);
}

CWaypoint* CWpDatabase::getPointerToWaypoint(string name){
		return CDatabase::getPointerToVal(name);

}

void CWpDatabase::print(){

	CDatabase::print();
}

const map<string, CWaypoint>& CWpDatabase::getDB() const{
	return CDatabase::getDB();
}

void CWpDatabase::clearDatabase(void){

	CDatabase::clearDatabase();
}
