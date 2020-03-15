#include <bits/stdc++.h>

using namespace std;

#include "math/two_sat.h"

#include <cppunit/extensions/HelperMacros.h>

class TwoSatTest : public CppUnit::TestFixture {
 public:
  void setUp() {}
  void tearDown() {}

  void testSolve() {
    TwoSat ts(3);
    ts.addClause(0, 1, 1, 0);
    ts.addClause(0, 0, 1, 1);
    ts.addClause(0, 0, 1, 0);
    ts.addClause(0, 1, 2, 0);
    bool status = ts.solve();
    CPPUNIT_ASSERT(status);

    const bool* mark = ts.getMark();
    for (int i = 0; i < 6; i++) {
      CPPUNIT_ASSERT(mark[i] == (i % 2 == 0));
    }
  }

  CPPUNIT_TEST_SUITE(TwoSatTest);
  CPPUNIT_TEST(testSolve);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(TwoSatTest);
