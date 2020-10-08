/*
 * CJsonPersistence.cpp
 *
 *  Created on: Dec 23, 2017
 *      Author: Tishan
 */

#include <ios>
#include <cstdlib>
#include <algorithm>

#include "CGPSSensor.h"
#include "CRoute.h"
#include "CNavigationSystem.h"
#include "CWaypoint.h"
#include "CPOI.h"
#include "CJsonPersistence.h"
#include "CWpDatabase.h"
#include "CPoiDatabase.h"
#include "CJsonStructure.h"

#include "CJsonScanner.h"
#include "CJsonToken.h"

using namespace std;


CJsonPersistence::CJsonPersistence(){}




void CJsonPersistence::setMediaName(string name){
	m_name = name + ".json";
}



bool CJsonPersistence::writeData(const CWpDatabase& waypointDb,
		const CPoiDatabase& poiDb){

	string name;
	double latitude;
	double longitude;
	t_poi type;
	string description;

	CJsonStructure jstruct,jarray;
	CJsonStructure jpoi,jpoiArray;

	this->m_storage.open(m_name.c_str(),m_storage.out);

	if((m_storage.rdstate() & ofstream::failbit)!=0){
		printError(WRITE,m_name,0);
		return true;
	}


	jstruct.setEncloser("{\n ","},\n");
	jarray.setEncloser("[ \n","],\n");

	map<string,CWaypoint> wp = waypointDb.getDB();
	map<string,CWaypoint>::iterator itrcopy;

	for(map<string,CWaypoint>::iterator itr = wp.begin(); itr!=wp.end(); ++itr){
		(*itr).second.getAllDataByReference(name,latitude,longitude);

		map<string,CWaypoint>::iterator itrcopy=itr;

		addStructToJson<string>(jstruct,3,"name",name," ",",\n");
		addStructToJson<double>(jstruct,6,"latitude",latitude," ",",\n");
		addStructToJson<double>(jstruct,6,"longitude",longitude," ","\n");

		if(++itrcopy == wp.end()){
			jstruct.setEncloser("{ \n","} \n");
		}else
			jstruct.setEncloser("{ \n" ,"},\n");

		jstruct.setLevel(6);
		jstruct.enclose();


		jarray.structAdd(jstruct);
		jstruct.clear();

	}

	jarray.setLevel(4);
	jarray.enclose();

	jstruct.setLevel(3);
	jstruct.setEncloser("{\n","}\n");
	jstruct.structAdd("waypoint",jarray);


	string typeStr;
	map<string,CPOI> poi = poiDb.getDB();

	jpoi.setEncloser("{ \n","},\n");
	jpoiArray.setEncloser("[ \n","] \n");

	for(map<string,CPOI>::iterator itr = poi.begin(); itr!=poi.end(); ++itr){
		(*itr).second.getAllDataByReference(name,latitude,longitude,type,description);

		switch(type){
		case RESTAURANT:
			typeStr = "RESTAURANT;";
			break;
		case TOURISTIC:
			typeStr = "TOURISTIC;";
			break;
		case GASSTATION:
			typeStr = "GASSTAION;";
			break;
		case UNIVERSITY:
			typeStr = "UNIVERSITY;";
			break;
		};

		map<string,CPOI>::iterator itrcopy=itr;


		addStructToJson<string>(jpoi,1,"name",name,"",",\n");
		addStructToJson<double>(jpoi,6,"latitude",latitude," ",",\n");
		addStructToJson<double>(jpoi,6,"longitude",longitude," ",",\n");
		addStructToJson<string>(jpoi,6,"type",typeStr," ",",\n");
		addStructToJson<string>(jpoi,6,"description",description," ","\n");

		if(++itrcopy == poi.end()){
			jpoi.setEncloser("{ \n","} \n");
		}else
			jpoi.setEncloser("{ \n" ,"},\n");

		jpoi.setLevel(6);
		jpoi.enclose();

		jpoiArray.structAdd(jpoi);
		jpoi.clear();
	}

	jpoiArray.setLevel(4);
	jpoiArray.enclose();

	jpoi.setLevel(3);
	jpoi.setEncloser("{","}");
	jpoi.structAdd("pois",jpoiArray);

	jstruct.structAdd(jpoi);

	jstruct.setLevel(1);
	jstruct.enclose();

	m_storage<<jstruct.getStream().str();

	this->m_storage.close();

	return false;
}

void CJsonPersistence::printError(int errorNo, string objName, int lineNo){

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

void CJsonPersistence::trim(string& obj){
	obj = obj.substr(obj.find_first_not_of(" \t"),obj.npos);
	obj = obj.substr(0,obj.find_last_not_of(" \t")+1);
}

bool CJsonPersistence::readData(CWpDatabase& waypointDb, CPoiDatabase& poiDb,
		MergeMode mode){

	string name,attribName,typeStr;
	double latitude;
	double longitude;
	t_poi type;
	string description;

	waypointDb.clearDatabase();
	poiDb.clearDatabase();
	this->m_storage.open(m_name.c_str(),m_storage.in);

	if((m_storage.rdstate() & ifstream::failbit)!=0){
		printError(READ,m_name,0);
		return true;
	}

	APT::CJsonScanner scnObj(m_storage);
	APT::CJsonToken *token;

	APT::CJsonNumberToken *nToken;
	APT::CJsonStringToken *sToken;
	APT::CJsonToken::TokenType event;


	CJsonPersistence::States state = IDLE;
	string db;
	CJsonPersistence::States action = IDLE;

	try{
		token = scnObj.nextToken();
	}
	catch(const std::invalid_argument& e){
		cout << "At line " <<scnObj.scannedLine() << ": " <<e.what() << endl;
		this->m_storage.close();
		return true;
	}
//	cout << "------IDLE--------------------"<<endl;
	while(token){


		nToken = dynamic_cast<APT::CJsonNumberToken*>(token);
		sToken = dynamic_cast<APT::CJsonStringToken*>(token);

	//	cout<<token->str()<<endl;

		event = token->getType();


		//		 APT::CJsonToken::BEGIN_OBJECT
		//		 APT::CJsonToken::BEGIN_ARRAY
		//		 APT::CJsonToken::NAME_SEPARATOR
		//		 APT::CJsonToken::VALUE_SEPARATOR
		//		 APT::CJsonToken::STRING
		//		 APT::CJsonToken::NUMBER
		//		 APT::CJsonToken::END_ARRAY
		//		 APT::CJsonToken::END_OBJECT
		//

		switch(state){
		case IDLE:
			if(event == APT::CJsonToken::BEGIN_OBJECT){
				state = WAITING_FOR_DB_NAME;
		//		cout << "------IDLE to WAITING_FOR_DB_NAME--------------------"<<endl;
			}
			if(event ==  APT::CJsonToken::VALUE_SEPARATOR){
				state = WAITING_FOR_DB_NAME;
		//		cout << "------IDLE to WAITING_FOR_DB_NAME--------------------"<<endl;

			}
			break;
		case WAITING_FOR_DB_NAME:
			if(event ==  APT::CJsonToken::STRING){
				action =   STORE_ATTRIBUTE_NAME;
				state = WAITING_FOR_NAME_SEPARATOR;
		//		cout << "------WAITING_FOR_DB_NAME to WAITING_FOR_NAME_SEPARATOR--------------------"<<endl;
			}

			break;
		case WAITING_FOR_DB_BEGIN:
			if(event == APT::CJsonToken::BEGIN_ARRAY){
				state = WAITING_FOR_BEGIN_OBJECT;
		//		cout << "------WAITING_FOR_DB_BEGIN to WAITING_FOR_BEGIN_OBJECT--------------------"<<endl;

			}
			else if(event == APT::CJsonToken::STRING){
				action = ASSIGN_VALUE_ACCORDING_TO_STORED_ATTRIBUTE_NAME;
				state = WAITING_FOR_VALUE_SEPARATOR;
			}
			else if (event == APT::CJsonToken::BEGIN_OBJECT){
				state = WAITING_FOR_ATTRIBUTE_NAME;
		//		cout << "------WAITING_FOR_DB_BEGIN to WAITING_FOR_ATTRIBUTE_NAME--------------------"<<endl;

			}
			break;

		case WAITING_FOR_ATTRIBUTE_NAME:
			if(event == APT::CJsonToken::STRING){
				action = STORE_ATTRIBUTE_NAME;
				state = WAITING_FOR_NAME_SEPARATOR;
		//		cout << "------WAITING_FOR_ATTRIBUTE_NAME to WAITING_FOR_NAME_SEPARATOR--------------------"<<endl;

			}else if (event == APT::CJsonToken::BEGIN_OBJECT){
				state = WAITING_FOR_ATTRIBUTE_NAME;
		//		cout << "------WAITING_FOR_ATTRIBUTE_NAME to WAITING_FOR_ATTRIBUTE_NAME--------------------"<<endl;

			}
			break;
		case WAITING_FOR_NAME_SEPARATOR:
			if(event ==  APT::CJsonToken::NAME_SEPARATOR){
				state = WAITING_FOR_VALUE;
		//		cout << "------WAITING_FOR_NAME_SEPARATOR to WAITING_FOR_VALUE--------------------"<<endl;

			}
			break;
		case WAITING_FOR_VALUE_SEPARATOR:
			if(event ==  APT::CJsonToken::VALUE_SEPARATOR){
				state = WAITING_FOR_ATTRIBUTE_NAME;
		//		cout << "------WAITING_FOR_VALUE_SEPARATOR to WAITING_FOR_ATTRIBUTE_NAME--------------------"<<endl;

			}
			else if(event == APT::CJsonToken::END_OBJECT){
				action = STORE_THE_OBJECT_IN_DB;
				state =  WAITING_FOR_END_ARRAY;
			//	cout << "------action : STORE_THE_OBJECT_IN_DB if action != SET_TO_IDLE-------"<<endl;
		//		cout << "------WAITING_FOR_VALUE_SEPARATOR to   WAITING_FOR_END_ARRAY--------------------"<<endl;
//
			}
			else if(event == APT::CJsonToken::END_ARRAY){
				state = IDLE;
		//		cout << "------WAITING_FOR_VALUE_SEPARATOR to IDLE--------------------"<<endl;

			}
			break;
		case WAITING_FOR_VALUE:
			if(event == APT::CJsonToken::BEGIN_ARRAY){
				state = WAITING_FOR_DB_BEGIN;
		//		cout << "------WAITING_FOR_VALUE to WAITING_FOR_DB_BEGIN--------------------"<<endl;

			}else if(event == APT::CJsonToken::STRING){
				action = ASSIGN_VALUE_ACCORDING_TO_STORED_ATTRIBUTE_NAME;
				state = WAITING_FOR_VALUE_SEPARATOR;

		//		cout << "------WAITING_FOR_VALUE to WAITING_FOR_VALUE_SEPARATOR--------------------"<<endl;

			}else if(event == APT::CJsonToken::NUMBER){
				action = ASSIGN_VALUE_ACCORDING_TO_STORED_ATTRIBUTE_NAME;
				state = WAITING_FOR_VALUE_SEPARATOR;
		//		cout << "------WAITING_FOR_VALUE to WAITING_FOR_VALUE_SEPARATOR--------------------"<<endl;

			}
			break;
		case WAITING_FOR_BEGIN_OBJECT:
			if(event ==  APT::CJsonToken::STRING){
				action = STORE_ATTRIBUTE_NAME;
				state = WAITING_FOR_NAME_SEPARATOR;
		//		cout << "------WAITING_FOR_BEGIN_OBJECT to WAITING_FOR_NAME_SEPARATOR--------------------"<<endl;

			} else if (event == APT::CJsonToken::BEGIN_OBJECT){
				state = WAITING_FOR_ATTRIBUTE_NAME;
		//		cout << "------WAITING_FOR_BEGIN_OBJECT to WAITING_FOR_ATTRIBUTE_NAME--------------------"<<endl;

			}
			break;
		case WAITING_FOR_END_OBJECT:
			if(event ==  APT::CJsonToken::VALUE_SEPARATOR){
				state = WAITING_FOR_DB_NAME;
		//		cout << "------WAITING_FOR_END_OBJECT to WAITING_FOR_DB_NAME--------------------"<<endl;

			}
			if(event ==  APT::CJsonToken::END_OBJECT){
				state = IDLE;
		//		cout << "------WAITING_FOR_END_OBJECT to IDLE--------------------"<<endl;

			}

			break;
		case WAITING_FOR_END_ARRAY:
			if(event ==  APT::CJsonToken::VALUE_SEPARATOR){
				state = WAITING_FOR_BEGIN_OBJECT;
		//		cout << "------WAITING_FOR_END_ARRAY to WAITING_FOR_BEGIN_OBJECT--------------------"<<endl;

			}
			else if (event == APT::CJsonToken::END_ARRAY){
				state =  WAITING_FOR_END_OBJECT;
		//		cout << "------WAITING_FOR_END_ARRAY to  WAITING_FOR_END_OBJECT--------------------"<<endl;

			}
			break;
		default:
			break;
		}


		switch(action){
		case IDLE:
			break;

		case STORE_ATTRIBUTE_NAME:
			if(sToken != NULL){
				attribName = sToken->getValue();
			}

			if(attribName == "waypoint" || attribName == "pois"){
				db = attribName;
		//		cout << "------db: " << db << "--------------------"<<endl;
			}else
		//		cout << "------attribName: " << attribName  << "--------------------"<<endl;

			action = IDLE;
			break;
		case ASSIGN_VALUE_ACCORDING_TO_STORED_ATTRIBUTE_NAME:
			if(attribName == "name"){
				if(sToken != NULL){
					name = sToken->getValue();
	//				cout << "------name: " << name  << "--------------------"<<endl;
				}
			}
			else if (attribName == "latitude"){
				if(nToken != NULL){
					latitude = nToken->getValue();
		//			cout << "------latitude: " << latitude  << "--------------------"<<endl;
				}
			}
			else if (attribName == "longitude"){
				if(nToken != NULL){
					longitude = nToken->getValue();
		//			cout << "------longitude: " << longitude  << "--------------------"<<endl;
				}
			}
			else if(attribName == "description"){
				if(sToken != NULL){
					description = sToken->getValue();
		//			cout << "------description: " << description  << "--------------------"<<endl;
				}
			}
			else if(attribName == "type"){
				if(sToken != NULL){
					typeStr = sToken->getValue();
		//			cout << "------type: " << type  << "--------------------"<<endl;
				}

				if(typeStr == "RESTAURANT"){
					type = RESTAURANT;
				}
				else if(typeStr == "TOURISTIC"){
					type = TOURISTIC;
				}
				else if(typeStr == "GASSTAION"){
					type = GASSTATION;
				}

				else if(typeStr == "UNIVERSITY"){
					type = UNIVERSITY;
				}
			}
			action = IDLE;
			break;
		case STORE_THE_OBJECT_IN_DB:
			if(db == "waypoint"){
				waypointDb.addWaypoint( CWaypoint(name,latitude,longitude));
		//		cout<<"------stored in waypoint "<< name << latitude<< longitude <<"---------------" <<endl;

			}
			else if(db == "pois"){
				poiDb.addPoi(CPOI(type,name,description,latitude,longitude));
		//		cout<<"------stored in pois "<< typeStr << name << description << latitude<< longitude <<"---------------"<< endl;

			}

			action = IDLE;
			break;

		default:
			action = IDLE;
			break;

		}

		try{
			token = scnObj.nextToken();
		}
		catch(const std::invalid_argument& e){
			cout << "Invalid Character(s) At line " <<scnObj.scannedLine() << ": " <<e.what() << endl;
			break;
		}
	//	cout<< endl;
	}


//	waypointDb.print();
//	poiDb.print();



	this->m_storage.close();
	return false;
}


