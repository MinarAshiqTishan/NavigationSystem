/*
 * CJsonPersistence.h
 *
 *  Created on: Dec 23, 2017
 *      Author: Tishan
 */

#ifndef CJSONPERSISTENCE_H_
#define CJSONPERSISTENCE_H_


#include <iostream>
#include <fstream>
#include "CJsonPersistence.h"
#include "CWpDatabase.h"
#include "CPoiDatabase.h"
#include "CJsonStructure.h"
#include "CJsonScanner.h"

using namespace std;


#define WRITE 1
#define READ 2
#define DELIM 3
#define TYPE 4
#define NAME 5
#define DESC 6
#define DIGIT 7
#define LAT 8
#define LON 9
#define LATR 10
#define LONR 11



class CJsonPersistence : CPersistentStorage
{

private:

	fstream m_storage;

	string m_name;


	template<typename T,typename U>
	bool write(const T& db, string className, CJsonStructure& jstruct);

	template<typename T>
	void addStructToJson(CJsonStructure& jstruct,int level,
			string name ,T& val,string start,string end);

	void printError(int errorNo,string objName, int lineNo);

	void trim(string& obj);


public:
	CJsonPersistence();

	void setMediaName(string name) ;

	bool writeData (const CWpDatabase& waypointDb,
			const CPoiDatabase& poiDb) ;// read from db write to file

	bool readData (CWpDatabase& waypointDb, CPoiDatabase& poiDb,
			MergeMode mode) ;//reads from file writes to db


	enum States{
		IDLE,
		WAITING_FOR_DB_NAME,
		WAITING_FOR_DB_BEGIN,
		WAITING_FOR_ATTRIBUTE_NAME,
		WAITING_FOR_NAME_SEPARATOR,
		WAITING_FOR_VALUE_SEPARATOR,
		WAITING_FOR_VALUE,
		WAITING_FOR_BEGIN_OBJECT,
		WAITING_FOR_END_OBJECT,
		WAITING_FOR_END_ARRAY,
		STORE_ATTRIBUTE_NAME,
		ASSIGN_VALUE_ACCORDING_TO_STORED_ATTRIBUTE_NAME,
		STORE_THE_OBJECT_IN_DB




	};

	void stateMachine(APT::CJsonScanner& scnObj,
			APT::CJsonToken *token,CJsonPersistence::States state,
			CWpDatabase& waypointDb, CPoiDatabase& poiDb);


};

template<typename T>
inline void CJsonPersistence::addStructToJson(CJsonStructure& jstruct, int level,
		string name, T& val, string start, string end)
{
	jstruct.setLevel(level);
	jstruct.structAdd(name,val);
	jstruct.setEncloser(start,end);
	jstruct.setLevel(1);
	jstruct.enclose();
}


#endif /* CJSONPERSISTENCE_H_ */
