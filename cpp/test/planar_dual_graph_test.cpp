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

  void testLocator() {
    PlanarDualGraph pdg(9, 12);
    for (int i = 1; i <= 3; i++) {
      for (int j = 1; j <= 3; j++) {
        pdg.addPoint(i*2, j*2);
      }
    }

    for (int i = 0; i <= 2; i++) {
      pdg.addEdge(i, i+3);
      pdg.addEdge(i+3, i+6);
    }
    for (int i = 0; i <= 6; i+=3) {
      pdg.addEdge(i, i+1);
      pdg.addEdge(i+1, i+2);
    }
    pdg.build();
    PlanarDualGraph::Locator locator(pdg, 6);
    locator.addQuery(3, 3);
    locator.addQuery(5, 5);
    locator.addQuery(3, 5);
    locator.addQuery(5, 3);
    locator.addQuery(1, 1);
    locator.addQuery(3, 3);
    locator.build();
    vector<int> expected = {0, 4, 2, 3, 1, 0};
    for (int i = 0; i < 6; i++) {
      CPPUNIT_ASSERT_EQUAL(expected[i], locator.region_[i]);
    }
  }

  void testLocator2() {
    PlanarDualGraph pdg(4, 5);
    pdg.addPoint(10, 4);
    pdg.addPoint(0, 18);
    pdg.addPoint(12, 4);
    pdg.addPoint(6, 18);
    pdg.addEdge(0, 2);
    pdg.addEdge(1, 3);
    pdg.addEdge(1, 2);
    pdg.addEdge(0, 1);
    pdg.addEdge(2, 3);
    pdg.build();
    CPPUNIT_ASSERT_EQUAL(1, pdg.outerRegion_);
    PlanarDualGraph::Locator locator(pdg, 1);
    locator.addQuery(5, 1);
    locator.build();
    CPPUNIT_ASSERT_EQUAL(1, locator.region_[0]);
  }

  CPPUNIT_TEST_SUITE(PlanarDualGraphTest);
  CPPUNIT_TEST(testBuild);
  CPPUNIT_TEST(testLocator);
  CPPUNIT_TEST(testLocator2);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(PlanarDualGraphTest);
