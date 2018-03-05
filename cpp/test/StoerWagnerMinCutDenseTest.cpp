#include <bits/stdc++.h>

using namespace std;

#include "StoerWagnerMinCutDense.h"

#include <cppunit/extensions/HelperMacros.h>

class StoerWagnerMinCutDenseTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testMinCut() {
        // example in the original paper
        StoerWagnerMinCutDense mincut(8);
        mincut.addEdge(0, 1, 2);
        mincut.addEdge(0, 4, 3);
        mincut.addEdge(1, 2, 3);
        mincut.addEdge(1, 4, 2);
        mincut.addEdge(1, 5, 2);
        mincut.addEdge(2, 3, 4);
        mincut.addEdge(2, 6, 2);
        mincut.addEdge(3, 6, 2);
        mincut.addEdge(3, 7, 2);
        mincut.addEdge(4, 5, 3);
        mincut.addEdge(5, 6, 1);
        mincut.addEdge(6, 7, 3);

        int cut = mincut.minimumCut();
        CPPUNIT_ASSERT_EQUAL(4, cut);
    }

    CPPUNIT_TEST_SUITE(StoerWagnerMinCutDenseTest);
    CPPUNIT_TEST(testMinCut);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(StoerWagnerMinCutDenseTest);

