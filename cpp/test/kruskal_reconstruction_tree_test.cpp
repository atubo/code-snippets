#include <bits/stdc++.h>

using namespace std;

#include "graph/kruskal_reconstruction_tree.h"

#include <cppunit/extensions/HelperMacros.h>

class KruskalReconstructionTreeTest : public CppUnit::TestFixture {
  using Graph = KruskalReconstructionTree::Graph;

 public:
  void setUp() {}
  void tearDown() {}

  void testKruskal() {
    KruskalReconstructionTree krt(4);
    krt.addEdge(0, 1, 50);
    krt.addEdge(1, 2, 100);
    krt.addEdge(2, 3, 40);
    krt.addEdge(0, 2, 60);
    krt.addEdge(0, 3, 150);
    krt.kruskal();

    const auto& g = krt.getTree();
    CPPUNIT_ASSERT_EQUAL(7, g.N);
    CPPUNIT_ASSERT_EQUAL(6, g.M);
    CPPUNIT_ASSERT(hasEdges(g, 6, set<int>{4, 5}));
    CPPUNIT_ASSERT(hasEdges(g, 4, set<int>{2, 3}));
    CPPUNIT_ASSERT(hasEdges(g, 5, set<int>{0, 1}));
  }
 private:
  bool hasEdges(const Graph& g, int u, const set<int>& s) {
    set<int> c;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
      int v = g.E[eidx].to;
      c.insert(v);
    }
    return c == s;
  }

  CPPUNIT_TEST_SUITE(KruskalReconstructionTreeTest);
  CPPUNIT_TEST(testKruskal);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(KruskalReconstructionTreeTest);
