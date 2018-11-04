#include <bits/stdc++.h>

using namespace std;

#include "data_structures/segment_in_fenwick.h"

#include <cppunit/extensions/HelperMacros.h>

class SegmentInFenwickTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        SegmentInFenwick tree(4, 4, 4);
        tree.add(1, 2, 2);
        tree.add(2, 1, 1);
        tree.add(3, 3, 3);
        tree.add(4, 0, 4);
        CPPUNIT_ASSERT_EQUAL(3, tree.query(2, 1, 2));
        CPPUNIT_ASSERT_EQUAL(5, tree.query(3, 2, 3));
        CPPUNIT_ASSERT_EQUAL(10, tree.query(4, 0, 3));
    }

    void testWeightIndexZero() {
        SegmentInFenwick tree(2, 2, 4);
        tree.add(1, 0, 1);
        tree.add(1, 1, 2);
        tree.add(2, 0, 3);
        tree.add(2, 1, 4);
        CPPUNIT_ASSERT_EQUAL(1, tree.query(1, 0, 0));
        CPPUNIT_ASSERT_EQUAL(3, tree.query(1, 0, 1));
        CPPUNIT_ASSERT_EQUAL(4, tree.query(2, 0, 0));
        CPPUNIT_ASSERT_EQUAL(10, tree.query(2, 0, 1));
    }

    CPPUNIT_TEST_SUITE(SegmentInFenwickTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST(testWeightIndexZero);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SegmentInFenwickTest);

