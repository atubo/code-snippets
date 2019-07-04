#include <bits/stdc++.h>
using namespace std;

#include "data_structures/fenwick_tree.h"

#include <cppunit/extensions/HelperMacros.h>


class FenwickTreeTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testSetAndGet() {
        FenwickTree ft(8);
        ft.set(2, 1);
        ft.set(4, 2);

        CPPUNIT_ASSERT_EQUAL(int64_t(0), ft.get(1));
        CPPUNIT_ASSERT_EQUAL(int64_t(1), ft.get(2));
        CPPUNIT_ASSERT_EQUAL(int64_t(1), ft.get(3));
        CPPUNIT_ASSERT_EQUAL(int64_t(3), ft.get(4));
    }

    void testLowerBound() {
        FenwickTree ft(8);
        ft.set(2, 1);
        ft.set(3, 2);
        ft.set(4, 3);
        CPPUNIT_ASSERT_EQUAL(3, ft.lowerBound(3));
        CPPUNIT_ASSERT_EQUAL(3, ft.lowerBound(2));
        CPPUNIT_ASSERT_EQUAL(2, ft.lowerBound(1));
        CPPUNIT_ASSERT_EQUAL(9, ft.lowerBound(10));
    }

    void testLowerBoundSizeNotPowerOf2() {
        FenwickTree ft(5);
        ft.set(1, 1);
        ft.set(2, 2);
        ft.set(3, 3);
        ft.set(4, 4);
        ft.set(5, 5);
        CPPUNIT_ASSERT_EQUAL(1, ft.lowerBound(0));
        CPPUNIT_ASSERT_EQUAL(1, ft.lowerBound(1));
        CPPUNIT_ASSERT_EQUAL(2, ft.lowerBound(2));
        CPPUNIT_ASSERT_EQUAL(2, ft.lowerBound(3));
        CPPUNIT_ASSERT_EQUAL(3, ft.lowerBound(4));
        CPPUNIT_ASSERT_EQUAL(3, ft.lowerBound(5));
        CPPUNIT_ASSERT_EQUAL(3, ft.lowerBound(6));
        CPPUNIT_ASSERT_EQUAL(4, ft.lowerBound(7));
        CPPUNIT_ASSERT_EQUAL(4, ft.lowerBound(8));
        CPPUNIT_ASSERT_EQUAL(4, ft.lowerBound(9));
        CPPUNIT_ASSERT_EQUAL(4, ft.lowerBound(10));
        CPPUNIT_ASSERT_EQUAL(5, ft.lowerBound(11));
        CPPUNIT_ASSERT_EQUAL(5, ft.lowerBound(15));
        CPPUNIT_ASSERT_EQUAL(6, ft.lowerBound(20));
    }

    void testLowerBoundWithZeros() {
        FenwickTree ft(9);
        ft.set(1, 1);
        CPPUNIT_ASSERT_EQUAL(1, ft.lowerBound(1));
    }

    void testUpperBound() {
        FenwickTree ft(5);
        ft.set(1, 1);
        ft.set(2, 2);
        ft.set(3, 3);
        ft.set(4, 4);
        ft.set(5, 5);
        CPPUNIT_ASSERT_EQUAL(1, ft.upperBound(0));
        CPPUNIT_ASSERT_EQUAL(2, ft.upperBound(1));
        CPPUNIT_ASSERT_EQUAL(2, ft.upperBound(2));
        CPPUNIT_ASSERT_EQUAL(3, ft.upperBound(3));
        CPPUNIT_ASSERT_EQUAL(3, ft.upperBound(4));
        CPPUNIT_ASSERT_EQUAL(3, ft.upperBound(5));
        CPPUNIT_ASSERT_EQUAL(4, ft.upperBound(6));
        CPPUNIT_ASSERT_EQUAL(4, ft.upperBound(7));
        CPPUNIT_ASSERT_EQUAL(4, ft.upperBound(8));
        CPPUNIT_ASSERT_EQUAL(4, ft.upperBound(9));
        CPPUNIT_ASSERT_EQUAL(5, ft.upperBound(10));
        CPPUNIT_ASSERT_EQUAL(5, ft.upperBound(11));
        CPPUNIT_ASSERT_EQUAL(6, ft.upperBound(15));
        CPPUNIT_ASSERT_EQUAL(6, ft.upperBound(20));
    }

    void testUpperBoundWithZeros() {
        FenwickTree ft(9);
        ft.set(1, 1);
        ft.set(5, 1);
        CPPUNIT_ASSERT_EQUAL(5, ft.upperBound(1));
    }

    CPPUNIT_TEST_SUITE(FenwickTreeTest);
    CPPUNIT_TEST(testSetAndGet);
    CPPUNIT_TEST(testLowerBound);
    CPPUNIT_TEST(testLowerBoundSizeNotPowerOf2);
    CPPUNIT_TEST(testLowerBoundWithZeros);
    CPPUNIT_TEST(testUpperBound);
    CPPUNIT_TEST(testUpperBoundWithZeros);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(FenwickTreeTest);
