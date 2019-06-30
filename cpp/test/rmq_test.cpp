#include <bits/stdc++.h>

using namespace std;

#include "data_structures/rmq.h"

#include <cppunit/extensions/HelperMacros.h>

class RmqTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        int a[5] = {0, 1, -2, 3, 5};
        Rmq rmq(a, 5);
        CPPUNIT_ASSERT_EQUAL(-2, rmq.rmq(2, 2));
        CPPUNIT_ASSERT_EQUAL(1, rmq.rmq(0, 1));
        CPPUNIT_ASSERT_EQUAL(1, rmq.rmq(0, 2));
        CPPUNIT_ASSERT_EQUAL(3, rmq.rmq(1, 3));
        CPPUNIT_ASSERT_EQUAL(5, rmq.rmq(0, 4));
    }

    CPPUNIT_TEST_SUITE(RmqTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(RmqTest);
