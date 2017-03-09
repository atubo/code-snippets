#include <bits/stdc++.h>
using namespace std;

#include "MergeTree.h"

#include <cppunit/extensions/HelperMacros.h>

class MergeTreeTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testNormalFlow() {
        vector<int> A = {1, 5, 2, 6, 3, 7, 4};
        MergeTree mt(A);
        CPPUNIT_ASSERT(mt.find_by_order(1, 4, 2) == 5);
        CPPUNIT_ASSERT(mt.find_by_order(3, 3, 0) == 6);
        CPPUNIT_ASSERT(mt.find_by_order(0, 6, 2) == 3);

        CPPUNIT_ASSERT(mt.order_of_key(1, 4, 4) == 2);
        CPPUNIT_ASSERT(mt.order_of_key(3, 3, 5) == 0);
        CPPUNIT_ASSERT(mt.order_of_key(0, 6, 2) == 1);
    }

    CPPUNIT_TEST_SUITE(MergeTreeTest);
    CPPUNIT_TEST(testNormalFlow);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MergeTreeTest);
