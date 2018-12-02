#include <bits/stdc++.h>

using namespace std;

#include "data_structures/kd_tree.h"

#include <cppunit/extensions/HelperMacros.h>

class KdTreeTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        KdTree kd(2);
        kd.insert(2, 3, 3);
        int ret = kd.query(1, 1, 3, 3);
        CPPUNIT_ASSERT_EQUAL(3, ret);
        kd.insert(2, 2, 2);
        ret = kd.query(2, 2, 3, 4);
        CPPUNIT_ASSERT_EQUAL(5, ret);
    }

    CPPUNIT_TEST_SUITE(KdTreeTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(KdTreeTest);
