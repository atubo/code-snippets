#include <bits/stdc++.h>

using namespace std;

#include "netflow/dinic.h"

#include <cppunit/extensions/HelperMacros.h>

class DinicTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testFlowCalc() {
        Dinic dinic(6, 10);

        dinic.addEdge(0, 1, 8);
        dinic.addEdge(0, 2, 4);
        dinic.addEdge(2, 1, 4);
        dinic.addEdge(1, 3, 2);
        dinic.addEdge(1, 4, 2);
        dinic.addEdge(2, 3, 1);
        dinic.addEdge(2, 4, 4);
        dinic.addEdge(3, 4, 6);
        dinic.addEdge(3, 5, 9);
        dinic.addEdge(4, 5, 7);

        CPPUNIT_ASSERT_EQUAL(8, dinic.dinic(0, 5));
    }

    CPPUNIT_TEST_SUITE(DinicTest);
    CPPUNIT_TEST(testFlowCalc);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(DinicTest);
