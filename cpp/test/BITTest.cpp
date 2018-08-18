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

    void testLowerBound() {
        BIT bit(8);
        bit.set(2, 1);
        bit.set(3, 2);
        bit.set(4, 3);
        CPPUNIT_ASSERT_EQUAL(3, bit.lowerBound(3));
        CPPUNIT_ASSERT_EQUAL(3, bit.lowerBound(2));
        CPPUNIT_ASSERT_EQUAL(2, bit.lowerBound(1));
        CPPUNIT_ASSERT_EQUAL(9, bit.lowerBound(10));
    }

    void testLowerBoundSizeNotPowerOf2() {
        BIT bit(5);
        bit.set(1, 1);
        bit.set(2, 2);
        bit.set(3, 3);
        bit.set(4, 4);
        bit.set(5, 5);
        CPPUNIT_ASSERT_EQUAL(1, bit.lowerBound(0));
        CPPUNIT_ASSERT_EQUAL(1, bit.lowerBound(1));
        CPPUNIT_ASSERT_EQUAL(2, bit.lowerBound(2));
        CPPUNIT_ASSERT_EQUAL(2, bit.lowerBound(3));
        CPPUNIT_ASSERT_EQUAL(3, bit.lowerBound(4));
        CPPUNIT_ASSERT_EQUAL(3, bit.lowerBound(5));
        CPPUNIT_ASSERT_EQUAL(3, bit.lowerBound(6));
        CPPUNIT_ASSERT_EQUAL(4, bit.lowerBound(7));
        CPPUNIT_ASSERT_EQUAL(4, bit.lowerBound(8));
        CPPUNIT_ASSERT_EQUAL(4, bit.lowerBound(9));
        CPPUNIT_ASSERT_EQUAL(4, bit.lowerBound(10));
        CPPUNIT_ASSERT_EQUAL(5, bit.lowerBound(11));
        CPPUNIT_ASSERT_EQUAL(5, bit.lowerBound(15));
        CPPUNIT_ASSERT_EQUAL(6, bit.lowerBound(20));
    }

    void testLowerBoundWithZeros() {
        BIT bit(9);
        bit.set(1, 1);
        CPPUNIT_ASSERT_EQUAL(1, bit.lowerBound(1));
    }

    void testUpperBound() {
        BIT bit(5);
        bit.set(1, 1);
        bit.set(2, 2);
        bit.set(3, 3);
        bit.set(4, 4);
        bit.set(5, 5);
        CPPUNIT_ASSERT_EQUAL(1, bit.upperBound(0));
        CPPUNIT_ASSERT_EQUAL(2, bit.upperBound(1));
        CPPUNIT_ASSERT_EQUAL(2, bit.upperBound(2));
        CPPUNIT_ASSERT_EQUAL(3, bit.upperBound(3));
        CPPUNIT_ASSERT_EQUAL(3, bit.upperBound(4));
        CPPUNIT_ASSERT_EQUAL(3, bit.upperBound(5));
        CPPUNIT_ASSERT_EQUAL(4, bit.upperBound(6));
        CPPUNIT_ASSERT_EQUAL(4, bit.upperBound(7));
        CPPUNIT_ASSERT_EQUAL(4, bit.upperBound(8));
        CPPUNIT_ASSERT_EQUAL(4, bit.upperBound(9));
        CPPUNIT_ASSERT_EQUAL(5, bit.upperBound(10));
        CPPUNIT_ASSERT_EQUAL(5, bit.upperBound(11));
        CPPUNIT_ASSERT_EQUAL(6, bit.upperBound(15));
        CPPUNIT_ASSERT_EQUAL(6, bit.upperBound(20));
    }

    void testUpperBoundWithZeros() {
        BIT bit(9);
        bit.set(1, 1);
        bit.set(5, 1);
        CPPUNIT_ASSERT_EQUAL(5, bit.upperBound(1));
    }

    CPPUNIT_TEST_SUITE(BITTest);
    CPPUNIT_TEST(testSetAndGet);
    CPPUNIT_TEST(testLowerBound);
    CPPUNIT_TEST(testLowerBoundSizeNotPowerOf2);
    CPPUNIT_TEST(testLowerBoundWithZeros);
    CPPUNIT_TEST(testUpperBound);
    CPPUNIT_TEST(testUpperBoundWithZeros);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(BITTest);
