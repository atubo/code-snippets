#include <bits/stdc++.h>

using namespace std;

#include "FenwickInFenwick.h"

#include <cppunit/extensions/HelperMacros.h>

class FenwickInFenwickTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        FenwickInFenwick ft(4, 3);
        ft.add(1, 1, 1);
        ft.add(2, 1, 2);
        ft.add(2, 2, 3);
        CPPUNIT_ASSERT_EQUAL(6, ft.query(1, 1, 2, 2));
        CPPUNIT_ASSERT_EQUAL(6, ft.query(1, 1, 4, 3));
        ft.add(3, 3, 4);
        ft.add(4, 2, 5);
        CPPUNIT_ASSERT_EQUAL(9, ft.query(3, 2, 4, 3));
        CPPUNIT_ASSERT_EQUAL(15, ft.query(1, 1, 4, 3));
    }

    CPPUNIT_TEST_SUITE(FenwickInFenwickTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(FenwickInFenwickTest);
