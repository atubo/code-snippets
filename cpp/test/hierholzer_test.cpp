#include <bits/stdc++.h>

using namespace std;

#include "graph/hierholzer.h"

#include <cppunit/extensions/HelperMacros.h>

class HierholzerTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testSolve() {
        Hierholzer hh(9);
        hh.addEdge(1, 2);
        hh.addEdge(2, 3);
        hh.addEdge(3, 8);
        hh.addEdge(8, 1);
        hh.addEdge(1, 0);
        hh.addEdge(0, 7);
        hh.addEdge(7, 1);
        hh.addEdge(7, 8);
        hh.addEdge(8, 5);
        hh.addEdge(5, 3);
        hh.addEdge(3, 4);
        hh.addEdge(4, 5);
        hh.addEdge(5, 6);
        hh.addEdge(6, 7);

        vector<int> path = hh.solve(1);
        vector<int> expected = {1, 2, 3, 8, 1, 0, 7, 8, 5, 3, 4, 5, 6,
                             7, 1};
        CPPUNIT_ASSERT(path == expected);
    }

    CPPUNIT_TEST_SUITE(HierholzerTest);
    CPPUNIT_TEST(testSolve);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(HierholzerTest);


