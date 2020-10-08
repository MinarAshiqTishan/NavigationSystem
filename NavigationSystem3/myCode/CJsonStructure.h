/*
 * CJsonStructure.h
 *
 *  Created on: Dec 23, 2017
 *      Author: Tishan
 */

#ifndef CJSONSTRUCTURE_H_
#define CJSONSTRUCTURE_H_

#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class CJsonStructure
{


private:
	ostringstream m_struct;
	string m_start;
	string m_end;
	int m_level;

public:
	CJsonStructure();

	void setEncloser(string start, string end);

	void setLevel(int level);

	void enclose ();

	void clear();

	void structAdd (string tokenString, string valString);

	void structAdd (string tokenString, double val);

	void structAdd (string tokenString, CJsonStructure& val);

	ostringstream& structAdd (CJsonStructure& structVal);

	ostringstream& getStream ();
};

#endif /* CJSONSTRUCTURE_H_ */
