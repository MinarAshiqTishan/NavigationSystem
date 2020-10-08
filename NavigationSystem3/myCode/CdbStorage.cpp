/*
 * CdbStorage.cpp
 *
 *  Created on: Dec 22, 2017
 *      Author: Tishan
 */

#include "CdbStorage.h"

#include<ios>
#include <cstdlib>
#include<algorithm>
#include "CGPSSensor.h"
#include "CRoute.h"
#include "CNavigationSystem.h"
#include "CWaypoint.h"
#include "CdbStorage.h"

#include "CDatabase.h"
#include "CPersistentStorage.h"
using namespace std;



void CdbStorage::printError(int errorNo, string objName, int lineNo)
{
	cout << "ERROR: ";

	switch(errorNo){
	case 1:
		cout << "can't open file " << objName <<" for writing" << endl;
		return;
		break;
	case 2:
		cout << "can't open file "<< objName <<" for reading" << endl;
		return;
		break;
	case 3:
		cout << "FIELD DELIMITER error";
		break;
	case 4:
		cout << "TYPE error";
		break;
	case 5:
		cout << "NAME MISSING";
		break;
	case 6:
		cout << "DESCRIPTION MISSING";
		break;
	case 7:
		cout << "NOT A DIGIT";
		break;
	case 8:
		cout << "LATITUDE MISSING";
		break;
	case 9:
		cout << "LONGITUDE MISSING";
		break;
	case 10:
		cout << "LATITUDE OUT of Range";
		break;
	case 11:
		cout << "LONGITUDE OUT of Range";
		break;
	};
	cout <<" in line " << lineNo <<":  '" << objName <<"'"<<endl;


}

void CdbStorage::trim(string& obj)
{/*
 * trims the string off of whitespace and tab at
 * the start and end
 * */
	obj = obj.substr(obj.find_first_not_of(" \t"),obj.npos);
	obj = obj.substr(0,obj.find_last_not_of(" \t")+1);
}

CdbStorage::CdbStorage()
{
	// TODO Auto-generated constructor stub

}

void CdbStorage::setMediaName(string name)
{
	wpName = name+"-wp.txt";
	poiName = name+"-poi.txt";
}

bool CdbStorage::writeData(const CWpDatabase& waypointDb,
		const CPoiDatabase& poiDb)
{
	string name;
	double latitude;
	double longitude;
	t_poi type;
	string description;

	this->wpStorage.open(wpName.c_str(),wpStorage.out);

	if((wpStorage.rdstate() & ofstream::failbit)!=0){
		//cout << "ERROR: "<<"can't open file" << wpName<<" for writing"<<endl;
		printError(WRITE,wpName,0);
		return true;
	}

	map<string,CWaypoint> wp = waypointDb.getDB();

	for(map<string,CWaypoint>::iterator itr = wp.begin(); itr!=wp.end(); ++itr){
		(*itr).second.getAllDataByReference(name,latitude,longitude);
		wpStorage << name<< ";" << latitude << ";" << longitude <<endl;
	}

	this->wpStorage.close();


	this->poiStorage.open(poiName.c_str(),poiStorage.out);

	if((poiStorage.rdstate() & ofstream::failbit)!=0){
		//cout << "ERROR: can't open file " << poiName<<" for writing"<<endl;
		printError(WRITE,poiName,0);

		return true;
	}


	map<string,CPOI> poi = poiDb.getDB();

	for(map<string,CPOI>::iterator itr = poi.begin(); itr!=poi.end(); ++itr){
		(*itr).second.getAllDataByReference(name,latitude,longitude,type,description);
		switch(type){
		case RESTAURANT:
			poiStorage << "RESTAURANT;";
			break;
		case TOURISTIC:
			poiStorage << "TOURISTIC;";
			break;
		case GASSTATION:
			poiStorage << "GASSTAION;";
			break;
		case UNIVERSITY:
			poiStorage << "UNIVERSITY;";
			break;
		};
		poiStorage << name <<";"<<description<<";"<<latitude<<";"<<longitude<<endl;
	}

	this->poiStorage.close();

	return false;
}

bool CdbStorage::readData(CWpDatabase& waypointDb, CPoiDatabase& poiDb,
		MergeMode mode)
{
	/* reads from file writes to db
	 */
	string wpStr,getWpStr;
	string poiStr,getPoiStr;

	string name;
	double latitude;
	double longitude;
	string tname;
	string temp;
	t_poi type;
	string description;

	this->wpStorage.open(wpName.c_str(),wpStorage.in);

	if((wpStorage.rdstate() & ifstream::failbit)!=0){
		printError(READ,wpName,0);
		return true;
	}

	this->poiStorage.open(poiName.c_str(),poiStorage.in);

	if((poiStorage.rdstate() & ifstream::failbit)!=0){
		printError(READ,poiName,0);
		return true;
	}


	if(mode == REPLACE){

		waypointDb.clearDatabase();
		poiDb.clearDatabase();
	}

	//waypointDb.print();
	//cout<<"--------------"<<endl;

	int i = 0;//line number in the file
	while(	getline(wpStorage,getWpStr)){

		wpStr = getWpStr;

		if(std::count(wpStr.begin(),wpStr.end(),';')!=2){
			printError(DELIM,getWpStr,i);
			continue;
		}

		name = wpStr.substr(0,wpStr.find(';'));
		trim(name);
		if(name.size() == 0){
			printError(NAME,getWpStr,i);
			continue;
		}

		wpStr = wpStr.substr(wpStr.find(";")+1,string::npos);
		temp = wpStr.substr(0,wpStr.find(";"));
		trim(temp);
		if(temp.size() == 0){
			printError(LAT,getWpStr,i);
			continue;
		}

		if(!isdigit(temp.c_str()[0])){
			printError(DIGIT,getWpStr,i);
			continue;
		}

		latitude = atof(temp.c_str());
		if(!(latitude >= -90 && latitude <= 90) ){

			printError(LATR,getWpStr,i);

			continue;
		}
		wpStr = wpStr.substr(wpStr.find(";")+1,string::npos);
		trim(wpStr);
		if(wpStr.size() == 0){
			printError(LON,getWpStr,i);
			continue;
		}
		if(!isdigit(temp.c_str()[0])){
			printError(DIGIT,getWpStr,i);
			continue;
		}
		longitude = atof(wpStr.c_str());

		if(!(longitude >= -180 && longitude <= 180 )){

			printError(LONR,getWpStr,i);

			continue;
		}
		waypointDb.addWaypoint(CWaypoint(name,latitude,longitude));
		i++;
	}
	//waypointDb.print();



	i=0;
	while(	getline(poiStorage,getPoiStr)){

		poiStr = getPoiStr;


		if(std::count(poiStr.begin(),poiStr.end(),';')!=4){
			//cout << "ERROR: FIELD DELIMITER ERROR in line " << i <<":  " << getPoiStr <<endl;
			printError(DELIM,getPoiStr,i);
			continue;
		}
		//cout<<"-----"<<endl;
		tname = poiStr.substr(0,poiStr.find(';'));
		trim(tname);

		if(tname.size() == 0) {
			printError(TYPE,getPoiStr,i);
			continue;
		}


		if(tname ==  "RESTAURANT")
			type = RESTAURANT;

		else if (tname =="TOURISTIC")
			type = TOURISTIC;

		else if (tname =="GASSTAION")
			type =  GASSTATION;

		else if (tname =="UNIVERSITY")
			type = UNIVERSITY;
		else{
			printError(TYPE,getPoiStr,i);
			continue;
		}


		poiStr = poiStr.substr(poiStr.find(";")+1,string::npos);
		name = poiStr.substr(0,poiStr.find(';'));
		trim(name);
		if(name.size() == 0) {
			printError(NAME,getPoiStr,i);

			continue;
		}
		poiStr = poiStr.substr(poiStr.find(";")+1,string::npos);
		description = poiStr.substr(0,poiStr.find(';'));
		trim(description);
		if(description.size() == 0){
			printError(DESC,getPoiStr,i);
			continue;
		}
		poiStr = poiStr.substr(poiStr.find(";")+1,string::npos);
		temp = poiStr.substr(0,poiStr.find(";"));
		trim(temp);
		if(temp.size() == 0){
			printError(LAT,getPoiStr,i);

			continue;
		}
		if(!isdigit(temp.c_str()[0])){
			printError(DIGIT,getPoiStr,i);
			continue;
		}

		latitude = atof(temp.c_str());

		if(!(latitude >= -90 && latitude <= 90) ){

			printError(LATR,getPoiStr,i);

			continue;
		}
		poiStr = poiStr.substr(poiStr.find(";")+1,string::npos);
		trim(poiStr);
		if(poiStr.size() == 0) {
			printError(LON,getPoiStr,i);

			continue;
		}
		if(!isdigit(temp.c_str()[0])){
			printError(DIGIT,getPoiStr,i);

			continue;
		}

		longitude = atof(poiStr.c_str());

		if(!(longitude >= -180 && longitude <= 180 )){

			printError(LONR,getPoiStr,i);

			continue;
		}

		poiDb.addPoi(CPOI(type, name, description, latitude, longitude));

		i++;
	}

	//	poiDb.print();


	wpStorage.close();
	poiStorage.close();

	return false;
}
