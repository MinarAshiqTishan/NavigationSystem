/*
 * CGPSSensor.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: Tishan
 */

#include<iostream>

#include "CWaypoint.h"
#include"CGPSSensor.h"

using namespace std;

CGPSSensor::CGPSSensor(){
// constructor method
}

CWaypoint CGPSSensor::getCurrentPosition(){
/* gets current attributes from the sensor.
 * the sensor is simulated by user input
 */
	CWaypoint curWayPoint;
	double latitude,longitude;
	cout << "GPS Sensor"<<endl;
	cout << "    Enter latitude: ";
	cin >> latitude;
	cout << "    Enter longitude: ";
	cin >> longitude;

	curWayPoint.set("",latitude,longitude);

	return curWayPoint;
}

