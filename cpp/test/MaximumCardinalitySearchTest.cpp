#include <bits/stdc++.h>

using namespace std;

#include "MaximumCardinalitySearch.h"

#include <cppunit/extensions/HelperMacros.h>

class MaximumCardinalitySearchTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testMcs() {
        MaximumCardinalitySearch mcs(7, 11);
        mcs.addEdge(0, 1);
        mcs.addEdge(0, 2);
        mcs.addEdge(1, 2);
        mcs.addEdge(1, 3);
        mcs.addEdge(2, 3);
        mcs.addEdge(2, 4);
        mcs.addEdge(3, 4);
        mcs.addEdge(3, 5);
        mcs.addEdge(4, 5);
        mcs.addEdge(4, 6);
        mcs.addEdge(5, 6);
        mcs.solve();

        vector<int> expected = {0, 1, 2, 3, 5, 4, 6};
        for (int i = 0; i < 7; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], mcs.peo[i]);
        }
    }

    CPPUNIT_TEST_SUITE(MaximumCardinalitySearchTest);
    CPPUNIT_TEST(testMcs);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MaximumCardinalitySearchTest);
