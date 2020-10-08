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
#include "CRoute.h"
#include "CPersistentStorage.h"
#include "CdbStorage.h"
#include "CJsonPersistence.h"

using namespace std;





int main (void)
{

	//cout<<"\ncreating wp obj\n-----------------------------"<<endl;

	CWaypoint amsterdam("Amsterdam", 52.3731,4.8922); //52.3702° N, 4.8952° E
	CWaypoint darmstadt("Darmstadt", 49.85, 8.6527); //49.8728° N, 8.6512° E
	CWaypoint berlin("Berlin",52.5166,13.4); //52.5200° N, 13.4050° E
	//CWaypoint tokio("Tokio",35.6895,139.6917); //35.6895° N, 139.6917° E
	CWaypoint newWaypoint;

	//cout<<"\ncreating db wp obj\n-----------------------------"<<endl;
	CWpDatabase db;


	//cout<<"\nadding values to dbwp\n------------------------------------"<<endl;
	db.addWaypoint(amsterdam);
	db.addWaypoint(darmstadt);
	db.addWaypoint(berlin);
	//db.addWaypoint(tokio);

	//cout<<"\nprinting dbwp after adding values\n------------------------------------"<<endl;
	//db.print();

	//cout<<"\ncreating poi obj\n-----------------------------"<<endl;
	CPOI mensa(RESTAURANT,"Mensa HDA","The best Mensa in the world",10,20);
	CPOI sitte(RESTAURANT,"sitte","More expensive but also good",11,22);
	CPOI berlinPoi(RESTAURANT,"Berlin","Berlin City Center",52.51,13.4);

	//cout<<"\ncreating poidb obj\n-----------------------------"<<endl;
	CPoiDatabase poidb;

	//cout<<"\nadding poi to poidb\n-----------------------------"<<endl;

	poidb.addPoi(mensa);
	poidb.addPoi(sitte);
	poidb.addPoi(berlinPoi);

	//cout<<"\nprinting POI db after adding values\n------------------------------------"<<endl;
	//poidb.print();


	CNavigationSystem ns;

	CJsonPersistence jps;

	jps.setMediaName("first");

	bool fileerror = jps.writeData(db,poidb);

	jps.readData(db,poidb,CPersistentStorage::REPLACE);
	if(fileerror) return 0;

	ns.run();

	return 0;
}
