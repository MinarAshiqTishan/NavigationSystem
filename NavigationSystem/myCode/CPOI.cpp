/*
 * CPOI.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: Tishan
 */

#include <iostream>
#include <string>

#include "CPOI.h"

using namespace std;

CPOI::CPOI(t_poi type, string name, string description, double latitude, double longitude){
//constructor method
	m_type = type;
	m_name = name;
	m_description = description;
	m_latitude = latitude;
	m_longitude = longitude;
}
//RESTAURANT,TOURISTIC,GASSTATION,UNIVERSITY
void CPOI::print(){
//prints every data about the point of interest
	cout << "Point of Interest" << endl << "================="<<endl;
	cout << " of type ";

	switch(m_type){
	case RESTAURANT:
		cout << "Restaurant";
		break;
	case TOURISTIC:
		cout << "Touristic";
		break;
	case GASSTATION:
		cout << "Gasstation";
		break;
	case UNIVERSITY:
		cout << "University";
		break;
	};

	cout << " : " << m_description << endl;
	CWaypoint::print(MMSS);
}

void CPOI::getAllDataByReference(string& name, double& latitude, double& longitude, t_poi* type, string& description){
//getter method to get all data in a single call
	name = this->m_name;
	latitude = this->m_latitude;
	longitude = this->m_longitude;
	*type = this->m_type;
	description = this->m_description;
}
