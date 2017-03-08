#include <bits/stdc++.h>
using namespace std;

#include "PartitionTree.h"

#include <cppunit/extensions/HelperMacros.h>

class PartitionTreeTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testNormalFlow() {
        vector<int> A = {1, 5, 2, 6, 3, 7, 4};
        PartitionTree pt(A);
        CPPUNIT_ASSERT(pt.find_by_order(1, 4, 3) == 5);
        CPPUNIT_ASSERT(pt.find_by_order(3, 3, 1) == 6);
        CPPUNIT_ASSERT(pt.find_by_order(0, 6, 3) == 3);
    }

    CPPUNIT_TEST_SUITE(PartitionTreeTest);
    CPPUNIT_TEST(testNormalFlow);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(PartitionTreeTest);

