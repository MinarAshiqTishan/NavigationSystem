/*
 * CWaypoint.h
 *
 *  Created on: Oct 22, 2017
 *      Author: Tishan
 */

#ifndef CWAYPOINT_H_
#define CWAYPOINT_H_

#include<string>
#include<ostream>
using namespace std;


//1.1.c to turn VERBOSE mode on, uncomment the following line of code
//#define SHOWADRESS 0

/* 1.1.f The header file is best file to define DEGREE and MMSS,
 * because every file that includes it gets access to the definitions*/
#define DEGREE 1
#define MMSS 2

#define R 6378.17 //Radius of Earth
#define PI 3.14159265

class CWaypoint{
//1.1.a class based on the UML diagram CWaypoint
protected:
	//name of the waypoint
	string m_name;
//
//	//latitude of the waypoint
	double m_latitude;
//
//	//longitude of the waypoint
	double m_longitude;

private:
	//Decimal to 'Degree minute second' converter for Longitude
	void transformLongitude2degmmss(int& deg, int& mm, double& ss) const;

	//Decimal to 'Degree minute second' converter for Latitude
	void transformLatitude2degmmss(int& deg, int& mm, double& ss) const;

public:
	//Constructor
	CWaypoint(string name = "noName", double latitude = 0, double longitude = 0);

	//setter method for setting the details of the waypoint
	void set(string name, double latitude,  double longitude);

	//getter method to get the name of the waypoint
	string getName() const;

	//getter method to get the latitude of the waypoint
	double getLatitude() const;

	//getter method to get the longitude of the waypoint
	double getLongitude() const;

	//getter method to get all data of the waypoint in one call
	void getAllDataByReference(string& name, double& latitude, double& longitude);

	//calculates the distance between this waypoint to the parameter waypoint object
	double calculateDistance(const CWaypoint& wp);

	//print the details of the waypoint in decimal or deg mm ss format
	virtual void print(int format);

	virtual ~CWaypoint(){}

	virtual ostream& output(ostream& lhs) const;

	friend ostream& operator<<(ostream& lhs, const CWaypoint& wp){

		return wp.output(lhs);
	}

};


#endif /* CWAYPOINT_H_ */
