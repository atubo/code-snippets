#include <bits/stdc++.h>
using namespace std;

#include "SpfaDfs.h"

#include <cppunit/extensions/HelperMacros.h>

class SpfaDfsTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testNegativeWeightCycle() {
        SpfaDfs::Graph g(3);
        g.addEdge(0, 1, 0);
        g.addEdge(1, 2, 1);
        g.addEdge(2, 0, -2);
        SpfaDfs spfa(g);
        CPPUNIT_ASSERT(!spfa.check(0));
    }

    void testNoNegativeWeightCycle() {
        SpfaDfs::Graph g(3);
        g.addEdge(0, 1, 0);
        g.addEdge(1, 2, 2);
        g.addEdge(2, 0, -1);
        SpfaDfs spfa(g);
        CPPUNIT_ASSERT(spfa.check(0));
    }

    CPPUNIT_TEST_SUITE(SpfaDfsTest);
    CPPUNIT_TEST(testNegativeWeightCycle);
    CPPUNIT_TEST(testNoNegativeWeightCycle);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SpfaDfsTest);
