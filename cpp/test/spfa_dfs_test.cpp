#include <bits/stdc++.h>
using namespace std;

#include "spfa_dfs.h"

#include <cppunit/extensions/HelperMacros.h>

class SpfaDfsTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testNegativeWeightCycle() {
        SpfaDfs spfa(3, 3);
        spfa.addEdge(0, 1, 0);
        spfa.addEdge(1, 2, 1);
        spfa.addEdge(2, 0, -2);
        CPPUNIT_ASSERT(!spfa.check());
    }

    void testNoNegativeWeightCycle() {
        SpfaDfs spfa(3, 3);
        spfa.addEdge(0, 1, 0);
        spfa.addEdge(1, 2, 2);
        spfa.addEdge(2, 0, -1);
        CPPUNIT_ASSERT(spfa.check());
    }

    void testNoZeroWeightCycle() {
        // this shouldn't hang
        SpfaDfs spfa(30, 60);
        for (int i = 0; i < 29; i++) {
            spfa.addEdge(i, i+1, 0);
            spfa.addEdge(i, i+1, 0);
        }
        CPPUNIT_ASSERT(spfa.check(true));
    }

    void testZeroWeightCycle() {
        SpfaDfs spfa(3, 3);
        spfa.addEdge(0, 1, 1);
        spfa.addEdge(1, 2, 2);
        spfa.addEdge(2, 0, -3);
        CPPUNIT_ASSERT(!spfa.check(true));
    }

    CPPUNIT_TEST_SUITE(SpfaDfsTest);
    CPPUNIT_TEST(testNegativeWeightCycle);
    CPPUNIT_TEST(testNoNegativeWeightCycle);
    CPPUNIT_TEST(testNoZeroWeightCycle);
    CPPUNIT_TEST(testZeroWeightCycle);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SpfaDfsTest);
