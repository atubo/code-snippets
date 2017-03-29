#include <bits/stdc++.h>

using namespace std;

#include "MincostMaxflow.h"

#include <cppunit/extensions/HelperMacros.h>

class MincostMaxflowTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testFlowCalc() {
        using namespace MincostMaxflowNS;
        S = 0, T = 4;
        addEdge(0, 1, 4, 10);
        addEdge(0, 2, 1, 8);
        addEdge(2, 1, 2, 5);
        addEdge(2, 3, 3, 10);
        addEdge(1, 3, 6, 2);
        addEdge(1, 4, 1, 7);
        addEdge(3, 4, 2, 4);
        CPPUNIT_ASSERT_EQUAL(55, mincostFlow());
    }

    CPPUNIT_TEST_SUITE(MincostMaxflowTest);
    CPPUNIT_TEST(testFlowCalc);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MincostMaxflowTest);
