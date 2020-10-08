/*
 * CJsonStructure.cpp
 *
 *  Created on: Dec 23, 2017
 *      Author: Tishan
 */
#include <iostream>
#include <string>
#include <iomanip>
#include "CJsonStructure.h"

using namespace std;

CJsonStructure::CJsonStructure(){
	m_level  = 1;
}

void CJsonStructure::structAdd(string tokenString, string valString){
	this->m_struct <<setw(m_level);
	this->m_struct << "\""<< tokenString<<"\": \"" << valString<< "\"";
}

void CJsonStructure::structAdd(string tokenString, double val){
	this->m_struct <<setw(m_level);
	this->m_struct << "\""<< tokenString<<"\": " << val;
}

void CJsonStructure::structAdd(string tokenString, CJsonStructure& val){
	this->m_struct <<setw(m_level);
	this->m_struct << "\""<< tokenString<<"\":" << val.getStream().str();
}


ostringstream& CJsonStructure::structAdd(CJsonStructure& structVal){
	this->m_struct  << structVal.getStream().str() ;
	return this->m_struct;
}

void CJsonStructure::setEncloser(string start, string end){
	m_start = start;
	m_end =  end;

}

void CJsonStructure::clear(){
	this->m_struct.str("");
	this->m_struct.clear();
}

ostringstream& CJsonStructure::getStream(){
	return this->m_struct;
}

void CJsonStructure::enclose(){
	ostringstream enclosed;
	enclosed <<setw(m_level)<< m_start << this->m_struct.str() <<setw(m_level)<< m_end;

	this->m_struct.str("");
	this->m_struct.clear();
	this->m_struct << enclosed.str();
}

void CJsonStructure::setLevel(int level){
	m_level = level;
}
