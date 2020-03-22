#include <bits/stdc++.h>

using namespace std;

#include "data_structures/persistent_segment_tree.h"

#include <cppunit/extensions/HelperMacros.h>

class PersistentSegmentTreeTest:public CppUnit::TestFixture {
 public:
  void setUp() {}
  void tearDown() {}

  void test() {
    PersistentSegmentTree pst(4, 4);
    pst.insert(1, 0, 2, 1);
    pst.insert(2, 1, 1, 1);
    pst.insert(3, 2, 3, 1);
    pst.insert(4, 3, 0, 1);
    CPPUNIT_ASSERT_EQUAL(2, pst.query(2, 1, 2));
    CPPUNIT_ASSERT_EQUAL(1, pst.query(2, 0, 1));
    CPPUNIT_ASSERT_EQUAL(3, pst.query(3, 1, 3));
    CPPUNIT_ASSERT_EQUAL(2, pst.query(4, 2, 3));
  }

  CPPUNIT_TEST_SUITE(PersistentSegmentTreeTest);
  CPPUNIT_TEST(test);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(PersistentSegmentTreeTest);
