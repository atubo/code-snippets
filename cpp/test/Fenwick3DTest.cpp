#include <bits/stdc++.h>

using namespace std;

#include "Fenwick3D.h"

#include <cppunit/extensions/HelperMacros.h>

class Fenwick3DTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        Fenwick3D ft(4, 4, 4);
        ft.add(1, 1, 1, 3);
        ft.add(1, 1, 2, 2);
        ft.add(2, 3, 3, 1);
        ft.add(3, 2, 4, 4);
        ft.add(4, 4, 2, 5);

        CPPUNIT_ASSERT_EQUAL(9, ft.query(3, 2, 2, 4, 4, 4));
        CPPUNIT_ASSERT_EQUAL(5, ft.query(2, 2, 1, 3, 3, 4));
        CPPUNIT_ASSERT_EQUAL(8, ft.query(1, 1, 2, 4, 4, 3));
    }

    CPPUNIT_TEST_SUITE(Fenwick3DTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(Fenwick3DTest);
