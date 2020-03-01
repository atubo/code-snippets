#include <bits/stdc++.h>

using namespace std;

#include "data_structures/lichao_segment_tree.h"

#include <cppunit/extensions/HelperMacros.h>

class LcSegmentTreeTest:public CppUnit::TestFixture {
 public:
  void setUp() {}
  void tearDown() {}

  void testNormal() {
    LcSegmentTree lc(8);
    lc.modify(0.5, 1, 1, 4);
    lc.modify(0.875, -1, 1, 8);
    lc.modify(0.125, 2.1, 1, 8);
    vector<double> expected{0, 2.225, 2.35, 2.5, 3.0,
      3.375, 4.25, 5.125, 6};
    for (int i = 1; i < 9; i++) {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[i], lc.query(i), 1e-9);
    }
  }

  void testCrossInMiddle() {
    LcSegmentTree lc(8);
    lc.modify(0.5, 1, 1, 4);
    lc.modify(0.875, -1, 1, 8);
    lc.modify(0.125, 2, 1, 8);
    vector<double> expected{0, 2.125, 2.25, 2.5, 3.0,
      3.375, 4.25, 5.125, 6};
    for (int i = 1; i < 9; i++) {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[i], lc.query(i), 1e-9);
    }
  }

  CPPUNIT_TEST_SUITE(LcSegmentTreeTest);
  CPPUNIT_TEST(testNormal);
  CPPUNIT_TEST(testCrossInMiddle);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(LcSegmentTreeTest);
