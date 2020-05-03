#include <bits/stdc++.h>

using namespace std;

#include "tree/base_tree.h"

#include <cppunit/extensions/HelperMacros.h>

class BaseTreeTest : public CppUnit::TestFixture {
 public:
  void setUp() {}
  void tearDown() {}

  void testBuild() {
    BaseTree bt(7);
    bt.addEdge(0, 1, 8);
    bt.addEdge(0, 3, 7);
    bt.addEdge(1, 2, 5);
    bt.addEdge(2, 4, 1);
    bt.addEdge(2, 5, 10);
    bt.addEdge(2, 6, 4);
    bt.addEdge(4, 6, 3);
    bt.build();
    vector<int> rng = {4, 6, 2};
    CPPUNIT_ASSERT(bt.rng_ == rng);
    CPPUNIT_ASSERT_EQUAL(3, bt.ring_->n_);
    vector<int> w = {3, 4, 1};
    vector<int64_t> d = {0, 0, 20};
    for (int i = 0; i < 3; i++) {
      CPPUNIT_ASSERT_EQUAL(w[i], bt.ring_->w[i]);
      CPPUNIT_ASSERT_EQUAL(d[i], bt.ring_->d[i]);
    }
  }

  CPPUNIT_TEST_SUITE(BaseTreeTest);
  CPPUNIT_TEST(testBuild);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(BaseTreeTest);

