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

#include "CCopyConstructorTest.h"
#include "CAssignOperatorTest.h"
#include "CAddPoiTest.h"
#include "CPrintTest.h"
#include "CAddOperatorTest.h"
#include "CDatabaseConnectionTest.h"


#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>



using namespace CppUnit;
using namespace APTTest;


int main (void){


	TextUi::TestRunner runner;


	runner.addTest( CCopyConstructorTest::suite() );
	runner.addTest( CAssignOperatorTest::suite() );
	runner.addTest( CAddPoiTest::suite() );
	runner.addTest( CPrintTest::suite() );
	runner.addTest( CAddOperatorTest::suite() );
	runner.addTest( CDatabaseConnectionTest::suite() );


	runner.run();

	return 0;
}
