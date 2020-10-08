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
void CPOI::print(int format){
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
		CWaypoint::print(format);
}

ostream& CPOI::output(ostream& lhs) const{
	/*
	 * this function streams objects
	 * of CWaypoint, whose internals are not accessible
	 * through their class' public interface,
	 * so the operator can't get at them.
	 * So I put this public member into the class
	 * which does the streaming
	*/

	lhs << "Point of Interest" << endl << "================="<<endl;
		lhs << " of type ";
		switch(this->m_type){
		case RESTAURANT:
			lhs << "Restaurant";
			break;
		case TOURISTIC:
			lhs << "Touristic";
			break;
		case GASSTATION:
			lhs << "Gasstation";
			break;
		case UNIVERSITY:
			lhs << "University";
			break;
		};
		lhs << " : " << m_description<<endl;
		CWaypoint::output(lhs);
		return lhs;
	}
void CPOI::getAllDataByReference(string& name, double& latitude, double& longitude, t_poi& type, string& description) const{
//getter method to get all data in a single call
	name = this->m_name;
	latitude = this->m_latitude;
	longitude = this->m_longitude;
	type = this->m_type;
	description = this->m_description;
}


//string CPOI::getName()const{
//	return this->m_name;
//}
//
//			//getter method to get the latitude of the waypoint
//double CPOI::getLatitude() const{
//	return this->m_latitude;
//}
//
//			//getter method to get the longitude of the waypoint
//double CPOI::getLongitude() const{
//	return this->m_longitude;
//}
