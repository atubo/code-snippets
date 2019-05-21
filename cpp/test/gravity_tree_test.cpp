#include <bits/stdc++.h>

using namespace std;

#include "tree/gravity_tree.h"

#include <cppunit/extensions/HelperMacros.h>

class GravityTreeTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testSolve() {
        GravityTree gt(7);
        gt.addEdge(0, 1, 1);
        gt.addEdge(2, 1, 1);
        gt.addEdge(3, 1, 1);
        gt.addEdge(4, 3, 1);
        gt.addEdge(4, 5, 1);
        gt.addEdge(4, 6, 1);

        gt.solve(0);

        vector<GravityTree::Dist> expected = {{3, 2, 0}, {1, 1, 0}, {0, 0, -1}};
        CPPUNIT_ASSERT(gt.fa_[0] == expected);

        expected = {{3, 1, 0}, {1, 0, -1}};
        CPPUNIT_ASSERT(gt.fa_[1] == expected);

        expected = {{3, 2, 0}, {1, 1, 1}, {2, 0, -1}};
        CPPUNIT_ASSERT(gt.fa_[2] == expected);

        expected = {{3, 0, -1}};
        CPPUNIT_ASSERT(gt.fa_[3] == expected);

        expected = {{3, 1, 1}, {4, 0, -1}};
        CPPUNIT_ASSERT(gt.fa_[4] == expected);

        expected = {{3, 2, 1}, {4, 1, 1}, {5, 0, -1}};
        CPPUNIT_ASSERT(gt.fa_[5] == expected);

        expected = {{3, 2, 1}, {4, 1, 2}, {6, 0, -1}};
        CPPUNIT_ASSERT(gt.fa_[6] == expected);
    }

    CPPUNIT_TEST_SUITE(GravityTreeTest);
    CPPUNIT_TEST(testSolve);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(GravityTreeTest);
