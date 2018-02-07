#include <bits/stdc++.h>

using namespace std;

#include "MincostMaxflow.h"

#include <cppunit/extensions/HelperMacros.h>

class MincostMaxflowTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testFlowCalc() {
        //using namespace MincostMaxflowNS;
        MincostMaxflow mincostMaxflow(5);
        mincostMaxflow.addEdge(0, 1, 4, 10);
        mincostMaxflow.addEdge(0, 2, 1, 8);
        mincostMaxflow.addEdge(2, 1, 2, 5);
        mincostMaxflow.addEdge(2, 3, 3, 10);
        mincostMaxflow.addEdge(1, 3, 6, 2);
        mincostMaxflow.addEdge(1, 4, 1, 7);
        mincostMaxflow.addEdge(3, 4, 2, 4);
        CPPUNIT_ASSERT(make_pair(11, 55) == mincostMaxflow.mincostFlow(0, 4));
    }

    CPPUNIT_TEST_SUITE(MincostMaxflowTest);
    CPPUNIT_TEST(testFlowCalc);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MincostMaxflowTest);
