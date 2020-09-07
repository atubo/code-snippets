#include <bits/stdc++.h>

using namespace std;

#include "computational_geometry/planar_dual_graph.h"

#include <cppunit/extensions/HelperMacros.h>

class PlanarDualGraphTest : public CppUnit::TestFixture {
 public:
  void setUp() {}
  void tearDown() {}

  void testBuild() {
    PlanarDualGraph pdg(6, 8);
    pdg.addPoint(-1, -1);
    pdg.addPoint(-1, 1);
    pdg.addPoint(0, -2);
    pdg.addPoint(0, 0);
    pdg.addPoint(1, -1);
    pdg.addPoint(1, 0);

    pdg.addEdge(0, 1);
    pdg.addEdge(0, 2);
    pdg.addEdge(0, 3);
    pdg.addEdge(1, 5);
    pdg.addEdge(2, 4);
    pdg.addEdge(2, 5);
    pdg.addEdge(3, 5);
    pdg.addEdge(4, 5);
    pdg.build();

    CPPUNIT_ASSERT_EQUAL(1, pdg.outerRegion_);
    CPPUNIT_ASSERT_EQUAL(4, pdg.rid_);
    vector<int> expected = {1, 0, 2, 1, 0, 2, 1, 0, 3, 1, 2, 3, 0, 2, 3, 1};
    for (int i = 0; i < 16; i++) {
      CPPUNIT_ASSERT_EQUAL(expected[i], pdg.enclose_[i]);
    }
    vector<int64_t> expectedAreas = {3, -8, 4, 1};
    for (int i = 0; i < 4; i++) {
      CPPUNIT_ASSERT_EQUAL(expectedAreas[i], pdg.areas_[i]);
    }
  }

  CPPUNIT_TEST_SUITE(PlanarDualGraphTest);
  CPPUNIT_TEST(testBuild);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(PlanarDualGraphTest);
