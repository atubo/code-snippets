#include <bits/stdc++.h>
using namespace std;

#include "BIT.h"

#include <cppunit/extensions/HelperMacros.h>


class BITTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testSetAndGet() {
        BIT bit(8);
        bit.set(2, 1);
        bit.set(4, 2);

        CPPUNIT_ASSERT_EQUAL(int64_t(0), bit.get(1));
        CPPUNIT_ASSERT_EQUAL(int64_t(1), bit.get(2));
        CPPUNIT_ASSERT_EQUAL(int64_t(1), bit.get(3));
        CPPUNIT_ASSERT_EQUAL(int64_t(3), bit.get(4));
    }

    void testGetind() {
        BIT bit(8);
        bit.set(2, 1);
        bit.set(3, 2);
        bit.set(4, 3);
        CPPUNIT_ASSERT_EQUAL(3, bit.getind(3));
        CPPUNIT_ASSERT_EQUAL(2, bit.getind(2));
        CPPUNIT_ASSERT_EQUAL(2, bit.getind(1));
        CPPUNIT_ASSERT_EQUAL(8, bit.getind(10));
    }

    void testGetindSizeNotPowerOf2() {
        BIT bit(5);
        bit.set(1, 1);
        bit.set(2, 2);
        bit.set(3, 3);
        bit.set(4, 4);
        bit.set(5, 5);
        CPPUNIT_ASSERT_EQUAL(0, bit.getind(0));
        CPPUNIT_ASSERT_EQUAL(1, bit.getind(1));
        CPPUNIT_ASSERT_EQUAL(1, bit.getind(2));
        CPPUNIT_ASSERT_EQUAL(2, bit.getind(3));
        CPPUNIT_ASSERT_EQUAL(2, bit.getind(4));
        CPPUNIT_ASSERT_EQUAL(2, bit.getind(5));
        CPPUNIT_ASSERT_EQUAL(3, bit.getind(6));
        CPPUNIT_ASSERT_EQUAL(3, bit.getind(7));
        CPPUNIT_ASSERT_EQUAL(3, bit.getind(8));
        CPPUNIT_ASSERT_EQUAL(3, bit.getind(9));
        CPPUNIT_ASSERT_EQUAL(4, bit.getind(10));
        CPPUNIT_ASSERT_EQUAL(4, bit.getind(11));
        CPPUNIT_ASSERT_EQUAL(5, bit.getind(15));
        CPPUNIT_ASSERT_EQUAL(5, bit.getind(20));
    }

    CPPUNIT_TEST_SUITE(BITTest);
    CPPUNIT_TEST(testSetAndGet);
    CPPUNIT_TEST(testGetind);
    CPPUNIT_TEST(testGetindSizeNotPowerOf2);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(BITTest);
