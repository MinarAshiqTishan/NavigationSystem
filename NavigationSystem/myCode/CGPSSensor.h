/*
 * CGPSSensor.h
 *
 *  Created on: Oct 23, 2017
 *      Author: Tishan
 */

#ifndef CGPSSENSOR_H_
#define CGPSSENSOR_H_

#include "CWaypoint.h"

class CGPSSensor{
public:
	//Constructor
	CGPSSensor();

	//gets current position and returns it as a CWaypoint object
	CWaypoint getCurrentPosition();
};



#endif /* CGPSSENSOR_H_ */
