#include <bits/stdc++.h>

using namespace std;

#include "graph/tarjan_articulation_point.h"

#include <cppunit/extensions/HelperMacros.h>

class TarjanArticulationPointTest:public CppUnit::TestFixture {
 public:
  void setUp() {}
  void tearDown() {}

  void testSolve() {
    TarjanArticulationPoint ap(5, 6);
    ap.addEdge(0, 1);
    ap.addEdge(0, 2);
    ap.addEdge(1, 2);
    ap.addEdge(4, 2);
    ap.addEdge(4, 3);
    ap.addEdge(2, 3);
    ap.solve();
    for (int i = 0; i < 5; i++) {
      CPPUNIT_ASSERT(ap.art_[i] == (i==2));
    }
  }

  void testNoArticulationPoint() {
    TarjanArticulationPoint ap(5, 5);
    ap.addEdge(0, 1);
    ap.addEdge(1, 2);
    ap.addEdge(2, 3);
    ap.addEdge(3, 4);
    ap.addEdge(4, 0);
    ap.solve();
    for (int i = 0; i < 5; i++) {
      CPPUNIT_ASSERT(!ap.art_[i]);
    }
  }


  CPPUNIT_TEST_SUITE(TarjanArticulationPointTest);
  CPPUNIT_TEST(testSolve);
  CPPUNIT_TEST(testNoArticulationPoint);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(TarjanArticulationPointTest);
