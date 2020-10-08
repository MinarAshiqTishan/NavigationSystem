/*
 * CDatabaseConnectionTest.h
 *
 *  Created on: Jan 18, 2018
 *      Author: Tishan
 */

#ifndef CDATABASECONNECTIONTEST_H_
#define CDATABASECONNECTIONTEST_H_




#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "CRoute.h"
using namespace APT;

namespace APTTest {

/**
 * This class implements several test cases related to the selection method.
 * Each test case is implemented
 * as a method testXXX. The static method suite() returns a TestSuite
 * in which all tests are registered.
 */
class CDatabaseConnectionTest: public CppUnit::TestFixture {
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
		amsterdam = new CWaypoint("Amsterdam", 52.3731,4.8922); //52.3702° N, 4.8952° E
		darmstadt  = new CWaypoint("Darmstadt", 49.85, 8.6527); //49.8728° N, 8.6512° E
		berlin = new CWaypoint("Berlin",52.5166,13.4); //52.5200° N, 13.4050° E
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

	void testWpDatabaseAddress() {

		const CWpDatabase* testdb = db;

		cr->connectToWpDatabase(db);

		CPPUNIT_ASSERT(testdb == db);

	}

	void testPoiDatabaseAddress() {

		const CPoiDatabase* testpoidb = poidb;

		cr->connectToPoiDatabase(poidb);

		CPPUNIT_ASSERT(testpoidb == poidb);




	}



	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Add Operator Test");


		suite->addTest(new CppUnit::TestCaller<CDatabaseConnectionTest>
		("The waypoint database address is same after connection to route", &CDatabaseConnectionTest::testWpDatabaseAddress));

		suite->addTest(new CppUnit::TestCaller<CDatabaseConnectionTest>
		("The poi database address is same after connection to route", &CDatabaseConnectionTest::testPoiDatabaseAddress));


		return suite;
	}
};

} /* namespace Test */



#endif /* CDATABASECONNECTIONTEST_H_ */
