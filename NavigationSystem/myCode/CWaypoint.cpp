/*
 * CWaypoint.cpp
 *
 *  Created on: Oct 22, 2017
 *      Author: Tishan
 */

#include<iostream>
#include<string>
#include<math.h>

#include"CWaypoint.h"

CWaypoint::CWaypoint(string name, double latitude, double longitude){
/* This is the Constructor method */
	set(name, latitude, longitude);

//1.1.c
//VERBOSE mode: turns on if SHOWADRESS is defined in the main file or header
#ifdef SHOWADRESS
	cout << "Address of the object : " << this << endl;
	cout << "name : " << this->m_name << " at "<< &(this->m_name) << endl;
	cout << "latitude : "<< this->m_latitude << " at "<< &(this->m_latitude)<<endl;
	cout << "longitude : "<< this->m_longitude<< " at "<< &(this->m_longitude)<<endl;
#endif
/* sizes of the variables
 * name : (this->m_name.size()) gives the length of the string.
 * 		  sizeof(this->m_name) gives the size of the variable, which is 32.
 * latitude :  8
 * longitude :  8
 * */
}


void CWaypoint::set(string name, double latitude,  double longitude){
/* 1.1.b this method checks the validity of the of latitude and longitude
 * and write the values to the attributes of CWaypoint class
*/
	this->m_name = name;

	if(!(latitude >= -90 && latitude <= 90 )){
		this->m_latitude = 0; //the value was invalid. so setting attribute to 0
	}else{
		this->m_latitude = latitude;
	}

	if(!(longitude >= -180 && longitude <= 180 )){
		this->m_longitude = 0;//the value was invalid. so setting attribute to 0
	}else{
		this->m_longitude = longitude;
	}


}


void CWaypoint::print(int format){
/* 1.1.e this method, depending on the format value, prints
 * longitude and latitude in decimal or deg mm ss format
 * */
	int deg, mm;
	double ss;
	cout << this->m_name <<" on" ;
	if(format == 1 ){
		cout << " latitude" << " = "<< this->m_latitude;
		cout << " and longitude" << " = "<< this->m_longitude<<endl;

	}else if(format==2){
		transformLatitude2degmmss(deg,mm,ss);
		cout << " latitude" << " = "<< deg << " deg " << mm << " min "<<ss<<" sec ";

		transformLongitude2degmmss(deg,mm,ss);
		cout << "and longitude" << " = "<< deg << " deg " << mm << " min "<<ss<<" sec "<<endl;
	}
}


void CWaypoint::transformLongitude2degmmss(int& deg, int& mm, double& ss){
/*This method converts longitude from decimal to 'degree minute second' format*/
	double temp = this->m_longitude;

	deg = (int)(this->m_longitude);

	temp = (temp - deg)*60;

	mm = (int)(temp);

	temp = (temp - mm)*60;

	ss = temp;
}

void CWaypoint::transformLatitude2degmmss(int& deg, int& mm, double& ss){
/*This method converts latitude from decimal to 'degree minute second' format*/

	double temp = this->m_latitude;

	deg = (int)this->m_latitude;

	temp = (temp - deg)*60;

	mm = (int)temp;

	temp = (temp - mm)*60;

	ss = temp;
}


string CWaypoint::getName(){
//with this method user can get the name
	return this->m_name;
}
double CWaypoint::getLatitude(){
//with this method user can get the latitude
	return this->m_latitude;
}
double CWaypoint::getLongitude(){
//with this method user can get the longitude
	return this->m_longitude;
}

void CWaypoint::getAllDataByReference(string& name, double& latitude, double& longitude){
//with this method user can get all the attribute values in a single call
	name = this->m_name;
	latitude = this->m_latitude;
	longitude = this->m_longitude;

}

double CWaypoint::calculateDistance(const CWaypoint& wp){
// this method calculates distance between two objects
// the object it takes as reference and this object
	double dist;
	double latitude_1 = this->m_latitude*PI/180;
	double latitude_2 = wp.m_latitude*PI/180;
	double longitude_1 = this->m_longitude*PI/180;
	double longitude_2 = wp.m_longitude*PI/180;

	dist = R * acos(sin(latitude_1) * sin(latitude_2) + cos(latitude_1) * cos(latitude_2)* cos(longitude_2 - longitude_1));
	return dist;
}


















