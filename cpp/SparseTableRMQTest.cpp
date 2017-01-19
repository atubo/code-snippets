#include <bits/stdc++.h>
using namespace std;

#include "SparseTableRMQ.h"

#include <boost/assign/list_of.hpp>

#include <cppunit/extensions/HelperMacros.h>

using namespace boost::assign;

class SparseTableRMQTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testSingleElement() {
        SparseTableRMQ rmq;
        rmq.N = 1;
        rmq.A = {5};

        rmq.preCompute();
        CPPUNIT_ASSERT(rmq.st[0][0] == 5);
        CPPUNIT_ASSERT(rmq.rmq(0, 0) == 5);
    }

    void testRMQ() {
        SparseTableRMQ rmq;
        rmq.N = 10;
        rmq.A = {1, 2, 3, 4, 5, 3, 4, 5, 2, 1};
        rmq.preCompute();
        CPPUNIT_ASSERT(rmq.st[0] == list_of(1)(1)(1)(1));
        CPPUNIT_ASSERT(rmq.st[1] == list_of(2)(2)(2)(2));
        CPPUNIT_ASSERT(rmq.st[2] == list_of(3)(3)(3)(1));
        CPPUNIT_ASSERT(rmq.st[3] == list_of(4)(4)(3)(INT_MAX));
        CPPUNIT_ASSERT(rmq.st[4] == list_of(5)(3)(3)(INT_MAX));
        CPPUNIT_ASSERT(rmq.st[5] == list_of(3)(3)(2)(INT_MAX));
        CPPUNIT_ASSERT(rmq.st[6] == list_of(4)(4)(1)(INT_MAX));
        CPPUNIT_ASSERT(rmq.st[7] == list_of(5)(2)(INT_MAX)(INT_MAX));
        CPPUNIT_ASSERT(rmq.st[8] == list_of(2)(1)(INT_MAX)(INT_MAX));
        CPPUNIT_ASSERT(rmq.st[9] == list_of(1)(INT_MAX)(INT_MAX)(INT_MAX));
    }

    CPPUNIT_TEST_SUITE(SparseTableRMQTest);
    CPPUNIT_TEST(testSingleElement);
    CPPUNIT_TEST(testRMQ);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SparseTableRMQTest);
