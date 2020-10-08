/*
 * CPOI.h
 *
 *  Created on: Oct 23, 2017
 *      Author: Tishan
 */

#ifndef CPOI_H_
#define CPOI_H_

#include <string>
#include "CWaypoint.h"

using namespace std;

enum t_poi{RESTAURANT,TOURISTIC,GASSTATION,UNIVERSITY};

class CPOI : public CWaypoint{
private:
	//type of the POI
	t_poi m_type;

	//a short description of the POI
	string m_description;
	/*
	 * Inherited attributes from CWaypoint
	 * protected:
		string m_name;
		double m_latitude;
		double m_longitude;
	*/

public:

	//prints the details of the POI
	void print();

	//Constructor
	CPOI(t_poi type = RESTAURANT, string name = "noName", string description = "noDescription", double latitude = 0, double longitude = 0);

	//gives all the data of the POI in one call
	void getAllDataByReference(string& name, double& latitude, double& longitude, t_poi* type, string& description);

	/*
	 * Inherited methods from CWaypoint
	 * public:
	 *  void set(string name, double latitude,  double longitude);
	 *	double calculateDistance(const CWaypoint& wp);
	 *	string getName();
	 *	double getLatitude();
	 *	double getLongitude();
	 *	void getAllDataByReference(string& name, double& latitude, double& longitude);
	 *	void print(int format);
	 */

};



#endif /* CPOI_H_ */
