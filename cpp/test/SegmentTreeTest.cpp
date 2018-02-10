#include <bits/stdc++.h>

using namespace std;

#include "SegmentTree.h"

#include <cppunit/extensions/HelperMacros.h>

class SegmentTreeTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        SegmentTree st(5);
        st.update(1, 1, 2);
        CPPUNIT_ASSERT_EQUAL(0LL, st.query(3, 5));
        CPPUNIT_ASSERT_EQUAL(2LL, st.query(1, 5));
        st.update(4, 2, 3);
        CPPUNIT_ASSERT_EQUAL(9LL, st.query(2, 3));
        CPPUNIT_ASSERT_EQUAL(10LL, st.query(1, 5));
    }

    CPPUNIT_TEST_SUITE(SegmentTreeTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SegmentTreeTest);

