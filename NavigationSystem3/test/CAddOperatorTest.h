/*
 * CAddOperatotTest.h
 *
 *  Created on: Jan 18, 2018
 *      Author: Tishan
 */

#ifndef CADDOPERATORTEST_H_
#define CADDOPERATORTEST_H_



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
class CAddOperatorTest: public CppUnit::TestFixture {
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

		cr->connectToPoiDatabase(poidb);
		cr->connectToWpDatabase(db);
		cr->addWaypoint("Amsterdam");
		cr->addWaypoint("Darmstadt");

		cr->addPoi("Mensa HDA","Darmstadt");
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

	void testAddition() {
		//	setUp();
		CRoute* tRoute1 = new CRoute;
		CRoute* tRoute2 = new CRoute;
		CRoute er;

		tRoute1->connectToPoiDatabase(poidb);
		tRoute1->connectToWpDatabase(db);


		tRoute2->connectToPoiDatabase(poidb);
		tRoute2->connectToWpDatabase(db);

		tRoute1->addWaypoint("Amsterdam");
		tRoute1->addPoi("sitte","Amsterdam");

		tRoute2->addWaypoint("Darmstadt");
		tRoute2->addPoi("Mensa HDA","Darmstadt");


		*tRoute2+="Berlin";



		er = *tRoute1 + *tRoute2;


		vector<const CWaypoint*> eroute = er.getRoute();
		vector<const CWaypoint*> croute = cr->getRoute();

		vector<const CWaypoint*>::const_iterator citr = croute.begin();
		vector<const CWaypoint*>::const_iterator eitr = eroute.begin();
		//
		//
		//

		for(; citr != croute.end(),eitr != eroute.end() ; citr++,eitr++){
			CPPUNIT_ASSERT_EQUAL((*citr)->getName(), (*eitr)->getName());
		}



		delete tRoute1;
		delete tRoute2;
		//tearDown();


	}

	void testDuplicateAreAdded() {
		//	setUp();
		CRoute* tRoute1 = new CRoute;
		CRoute* tRoute2 = new CRoute;
		CRoute er;

		tRoute1->connectToPoiDatabase(poidb);
		tRoute1->connectToWpDatabase(db);


		tRoute2->connectToPoiDatabase(poidb);
		tRoute2->connectToWpDatabase(db);

		tRoute1->addWaypoint("Amsterdam");
		tRoute1->addWaypoint("Darmstadt");

		tRoute2->addPoi("sitte","Amsterdam");

		tRoute2->addPoi("Mensa HDA","Darmstadt");


		*tRoute2+="Berlin";

		tRoute2->addWaypoint("Amsterdam");
		tRoute2->addWaypoint("Darmstadt");



		er = *tRoute1 + *tRoute2;

		int count = 0;

		vector<const CWaypoint*> eroute = er.getRoute();
		vector<const CWaypoint*> croute = cr->getRoute();

		vector<const CWaypoint*>::const_iterator citr = croute.begin();
		vector<const CWaypoint*>::const_iterator eitr = eroute.begin();
		//
		//
		//

		for(; eitr != eroute.end() ; eitr++){
			count++;
		}

		CPPUNIT_ASSERT(count > 6);



		delete tRoute1;
		delete tRoute2;
		//tearDown();


	}



	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Add Operator Test");


		suite->addTest(new CppUnit::TestCaller<CAddOperatorTest>
		("All poi and waypoints are added", &CAddOperatorTest::testAddition));

		suite->addTest(new CppUnit::TestCaller<CAddOperatorTest>
		("Duplicate waypoints are also added from the Other route", &CAddOperatorTest::testDuplicateAreAdded));


		return suite;
	}
};

} /* namespace Test */




#endif /* CADDOPERATORTEST_H_ */
