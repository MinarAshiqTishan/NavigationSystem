/*
 * CPrintTest.h
 *
 *  Created on: Jan 18, 2018
 *      Author: Tishan
 */

#ifndef CPRINTTEST_H_
#define CPRINTTEST_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <stdexcept>

#include "CRoute.h"
using namespace APT;

namespace APTTest {

/**
 * This class implements several test cases related to the selection method.
 * Each test case is implemented
 * as a method testXXX. The static method suite() returns a TestSuite
 * in which all tests are registered.
 */
class CPrintTest: public CppUnit::TestFixture {
private:
	CRoute* cr;
	CWaypoint* amsterdam;
	CWaypoint* darmstadt;
	CWaypoint* berlin;
	CPOI* mensa;
	CPOI* sitte;
	CPOI* berlinPoi;
	CWpDatabase* db;
	CPoiDatabase* poidb;
public:

	void setUp() {
		cr = new CRoute;
		amsterdam = new CWaypoint("Amsterdam", 52.3731,4.8922); //52.3702� N, 4.8952� E
		darmstadt  = new CWaypoint("Darmstadt", 49.85, 8.6527); //49.8728� N, 8.6512� E
		berlin = new CWaypoint("Berlin",52.5166,13.4); //52.5200� N, 13.4050� E
		db = new CWpDatabase;
		db->addWaypoint(*amsterdam);
		db->addWaypoint(*darmstadt);
		db->addWaypoint(*berlin);
		mensa = new CPOI(RESTAURANT,"Mensa HDA","The best Mensa in the world",10,20);
		sitte = new CPOI(RESTAURANT,"sitte","More expensive but also good",11,22);
		berlinPoi = new CPOI(RESTAURANT,"Berlin","Berlin City Center",52.51,13.4);
		poidb = new CPoiDatabase;
		poidb->addPoi(*mensa);
		poidb->addPoi(*sitte);
		poidb->addPoi(*berlinPoi);

		cr->connectToPoiDatabase(poidb);
		cr->connectToWpDatabase(db);
		cr->addWaypoint("Amsterdam");
		cr->addWaypoint("Darmstadt");

		cr->addPoi("Mensa HDA","Tokio");
		cr->addPoi("sitte","Amsterdam");

		*cr+="Berlin";

	}
	//
	void tearDown() {

		delete amsterdam;
		delete darmstadt;
		delete berlin;
		delete mensa;
		delete sitte;
		delete berlinPoi;
		delete db;
		delete poidb;
		delete cr;
	}
	//


	void testPrintEmpty() {
		CRoute* dr = new CRoute;

		CPPUNIT_ASSERT_THROW( dr->print(), std::runtime_error );

		delete dr;
		//tearDown();
	}



	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Print Test");


		suite->addTest(new CppUnit::TestCaller<CPrintTest>
		("Printing Empty Route gives exception", &CPrintTest::testPrintEmpty));

		return suite;
	}
};

} /* namespace Test */







#endif /* CPRINTTEST_H_ */
