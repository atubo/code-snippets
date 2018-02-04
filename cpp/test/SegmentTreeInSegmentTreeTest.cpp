#include <bits/stdc++.h>
#include <cppunit/extensions/HelperMacros.h>
using namespace std;

#include "SegmentTreeInSegmentTree.h"

class SegmentTreeInSegmentTreeTest:public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(SegmentTreeInSegmentTreeTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp() {}
    void tearDown() {}
    void test();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SegmentTreeInSegmentTreeTest);

void SegmentTreeInSegmentTreeTest::test() {
    SegmentTreeInSegmentTree st(8, 8);
    st.put(1, 1, 1);
    CPPUNIT_ASSERT_EQUAL(1, st.query(1, 1, 1, 1));
    CPPUNIT_ASSERT_EQUAL(1, st.query(1, 4, 1, 4));

    st.put(2, 2, 2);
    st.put(3, 3, 3);
    st.put(4, 4, 4);
    st.put(5, 4, 2);
    CPPUNIT_ASSERT_EQUAL(2, st.query(1, 2, 1, 3));
    CPPUNIT_ASSERT_EQUAL(3, st.query(2, 3, 1, 4));
    CPPUNIT_ASSERT_EQUAL(4, st.query(3, 4, 3, 4));
    CPPUNIT_ASSERT_EQUAL(5, st.query(2, 4, 1, 4));
    CPPUNIT_ASSERT_EQUAL(5, st.query(1, 4, 1, 4));
}
