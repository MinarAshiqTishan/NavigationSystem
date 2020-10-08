// GIT-Labor
// main.cpp
//	Project type: GIT/SWE-Project(GCC)
//	Toolchains: MinGW GCC(GIT)
//	std: C++98
////////////////////////////////////////////////////////////////////////////////
// Header-Dateien
#include <iostream>
#include <stdlib.h>
#include <string>

#include "CWaypoint.h"
#include "CPOI.h"
#include "CNavigationSystem.h"

using namespace std;

int main (void)
{
	string name;
	double longitude;
	double latitude;

	cout << "Constructor" << endl << "==========="<<endl;

	//1.1.d four CWaypoint objects are created.
	//values are taken form google
	CWaypoint amsterdam("Amsterdam", 52.3702,4.8952); //52.3702° N, 4.8952° E
	CWaypoint darmstadt("Darmstadt", 49.8728, 8.6512); //49.8728° N, 8.6512° E
	CWaypoint berlin("Berlin",52.5200,13.4050); //52.5200° N, 13.4050° E
	CWaypoint tokio("Tokio",35.6895,139.6917); //35.6895° N, 139.6917° E
	CWaypoint newWaypoint;

	//1.1.f printing berlin in both formats
	cout << "Print Method" << endl << "============"<<endl;
	berlin.print(DEGREE);
	berlin.print(MMSS);

	//1.1.g testing the getter methods
	amsterdam.getLatitude();
	amsterdam.getLongitude();
	cout << "Name as return value : " << amsterdam.getName()<<endl;
	cout<<endl;



	//1.1.h getting all waypoint data in a single call
	tokio.getAllDataByReference(name,latitude,longitude);

/*	analyzing the addresses of the
 *  local variables and the parameter addresses,

	local:
		name 0x23fd00
		longitude 0x23fcf8
		latitude  0x23fcf0

	In the getAllDataByReference method:
		name 0x23fd00
		longitude 0x23fcf8 @0x23fcf8
		latitude 0x23fcf0 @0x23fcf0

	the address of the local variable
	and the referenced parameters are same
*/

	//1.1.i testcases calculating distance between
	//amsterdam and berlin
	//and berlin and tokio
	cout << "And a first real method" << endl << "======================="<<endl;
	cout << "Distance between Amsterdam and Berlin: " << amsterdam.calculateDistance(berlin)<<endl;
	cout << "Distance between Berlin and Tokio: " << berlin.calculateDistance(tokio)<<endl;
	cout<<endl;


	//1.3 running the CNavigation System
	CNavigationSystem cnsObj;
	cnsObj.run();

	return 0;
}
