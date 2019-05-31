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
        int A[1] = {5};
        SparseTableRMQ rmq(A, 1);

        CPPUNIT_ASSERT(rmq.rmq(0, 0) == 5);
    }

    void testRMQ() {
        int A[10] = {1, 2, 3, 4, 5, 3, 4, 5, 2, 1};
        SparseTableRMQ rmq(A, 10);
        CPPUNIT_ASSERT_EQUAL(3, rmq.rmq(0, 2));
        CPPUNIT_ASSERT_EQUAL(5, rmq.rmq(2, 5));
        CPPUNIT_ASSERT_EQUAL(3, rmq.rmq(5, 5));
    }

    CPPUNIT_TEST_SUITE(SparseTableRMQTest);
    CPPUNIT_TEST(testSingleElement);
    CPPUNIT_TEST(testRMQ);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SparseTableRMQTest);
