#include <bits/stdc++.h>

using namespace std;

#include "SegmentForest.h"

#include <cppunit/extensions/HelperMacros.h>

class SegmentForestTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        SegmentForest sf(3, 4, 6);
        sf.insert(0, 1, 1);
        sf.insert(0, 2, 2);
        sf.insert(1, 0, 2);
        sf.insert(1, 3, 3);
        sf.insert(2, 0, 3);
        sf.insert(2, 2, 4);
        CPPUNIT_ASSERT_EQUAL(1, sf.query(0, 0, 1));
        CPPUNIT_ASSERT_EQUAL(3, sf.query(0, 0, 2));
        CPPUNIT_ASSERT_EQUAL(0, sf.query(1, 1, 2));
        CPPUNIT_ASSERT_EQUAL(3, sf.query(1, 2, 3));
        CPPUNIT_ASSERT_EQUAL(0, sf.query(2, 1, 1));
        CPPUNIT_ASSERT_EQUAL(7, sf.query(2, 0, 2));
        CPPUNIT_ASSERT_EQUAL(7, sf.query(2, 0, 3));
    }

    CPPUNIT_TEST_SUITE(SegmentForestTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SegmentForestTest);
