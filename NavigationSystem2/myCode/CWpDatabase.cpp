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

CWpDatabase::CWpDatabase(){
	// TODO Auto-generated constructor stub

}

void CWpDatabase::addWaypoint(const CWaypoint& wp){

	m_wp.insert((make_pair(wp.getName(),wp)));

}

CWaypoint* CWpDatabase::getPointerToWaypoint(string name){
	//this->print();
	//cout<<endl;
	map<string,CWaypoint>::iterator itr =  m_wp.find(name);
		if (itr != m_wp.end()){
		//	cout<<"get pointer wp "<<&((*itr).second)<<endl;
			return &((*itr).second);
		}
		cout <<"ERROR: could not find Waypoint. '"<<name<<"' not in the pool"<<endl;
		return NULL;

}

void CWpDatabase::print(){
	for(map<string,CWaypoint>::iterator itr =  m_wp.begin();itr!=m_wp.end();++itr){
		(*itr).second.print(DEGREE);
		//cout<<&((*itr).second)<<endl;//<-address of the object
	}
}

const map<string, CWaypoint>& CWpDatabase::getDB() const{
	return m_wp;
}

void CWpDatabase::clearDatabase(void){
	this->m_wp.clear();
}
