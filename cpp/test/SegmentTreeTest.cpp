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
    CPPUNIT_ASSERT_EQUAL(int64_t(0), st.query(3, 5));
    CPPUNIT_ASSERT_EQUAL(int64_t(2), st.query(1, 5));
    st.update(4, 2, 3);
    CPPUNIT_ASSERT_EQUAL(int64_t(9), st.query(2, 3));
    CPPUNIT_ASSERT_EQUAL((int64_t)10, st.query(1, 5));
  }

  CPPUNIT_TEST_SUITE(SegmentTreeTest);
  CPPUNIT_TEST(test);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SegmentTreeTest);

