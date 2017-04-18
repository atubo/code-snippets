#include <bits/stdc++.h>

using namespace std;

#include "Dinic.h"

#include <cppunit/extensions/HelperMacros.h>

class DinicTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testFlowCalc() {
        Dinic::init();
        Dinic::end = 5;

        Dinic::addEdge(0, 1, 8);
        Dinic::addEdge(0, 2, 4);
        Dinic::addEdge(2, 1, 4);
        Dinic::addEdge(1, 3, 2);
        Dinic::addEdge(1, 4, 2);
        Dinic::addEdge(2, 3, 1);
        Dinic::addEdge(2, 4, 4);
        Dinic::addEdge(3, 4, 6);
        Dinic::addEdge(3, 5, 9);
        Dinic::addEdge(4, 5, 7);

        CPPUNIT_ASSERT_EQUAL(8, Dinic::dinic());
    }

    CPPUNIT_TEST_SUITE(DinicTest);
    CPPUNIT_TEST(testFlowCalc);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(DinicTest);
