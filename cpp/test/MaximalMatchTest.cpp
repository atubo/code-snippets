#include <bits/stdc++.h>
using namespace std;

#include "MaximalMatch.cpp"

#include <cppunit/extensions/HelperMacros.h>

class HungarianTest:public CppUnit::TestFixture {
public:
	void setUp() {}
	void tearDown() {}

	void testMaxMatch() {
		Hungarian hungarian;
        hungarian.reset(3, 4);
		int result = hungarian.maxMatch();
		CPPUNIT_ASSERT(result == 0);

        hungarian.reset(3, 4);
        hungarian.addEdge(0, 0);
        hungarian.addEdge(0, 2);
        hungarian.addEdge(1, 1);
        hungarian.addEdge(2, 0);
        hungarian.addEdge(2, 2);
        hungarian.addEdge(2, 3);

		result = hungarian.maxMatch();
		CPPUNIT_ASSERT(result == 3);

	}

	CPPUNIT_TEST_SUITE(HungarianTest);
	CPPUNIT_TEST(testMaxMatch);
	CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(HungarianTest);
