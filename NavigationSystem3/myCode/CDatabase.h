/*
 * CPoiDatabase.h
 *
 *  Created on: Oct 23, 2017
 *      Author: Tishan
 */

#ifndef CDATABASE_H_
#define CDATABASE_H_

#include <iostream>
#include <string>
#include <map>

using namespace std;

template<class T>
class CDatabase{
private:
	//array of CPOI objects that acts as the container for the database
//	CPOI m_POI[10];

	map<string,T> m_val;



public:
	//Constructor
	CDatabase();

	//creates a CPOI object from parameters and adds it to the database
	void add(const T& val);

	//returns a pointer to the matching POI in the database
	T* getPointerToVal(string name);
	const map<string,T>& getDB()const;
	void clearDatabase(void);
	void print();
};

template<class T>
CDatabase<T>::CDatabase(){
//constructor

}

template<class T>
void CDatabase<T>::add(const T& val){
/* this method adds POI objects
*/

	m_val.insert( make_pair(val.getName(),val) );

}

template<class T>
T* CDatabase<T>::getPointerToVal(string name){
/* returns a pointer the matching POI object from the database.
 * if the matching POI does not exist, it returns a NULL and
 * shows a warning
*/
	typename map<string, T>::iterator itr =  m_val.find(name);
	if (itr != m_val.end()){
	//	cout<<"get pointer poi "<<&((*itr).second)<<endl;
		return &((*itr).second);
	}



	cout <<"ERROR: could not find POI.'"<<name<<"' not in the pool"<<endl;
	return NULL;
}

template<class T>
void CDatabase<T>::print(){
	for(typename map<string, T>::iterator itr =  m_val.begin();itr!=m_val.end();++itr){
		cout<<(*itr).second<<endl;
		//cout<<&((*itr).second)<<endl;//<-address of the object
	}
}

template<class T>
const map<string, T>& CDatabase<T>::getDB() const{
	return m_val;
}

template<class T>
void CDatabase<T>::clearDatabase(void){
	this->m_val.clear();
}


#endif /* CDATABASE_H_ */
