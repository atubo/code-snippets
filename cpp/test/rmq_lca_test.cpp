#include <bits/stdc++.h>
using namespace std;

#include "tree/rmq_lca.h"

#include <cppunit/extensions/HelperMacros.h>

class RmqLcaTest:public CppUnit::TestFixture {
 public:
  void setUp() {}
  void tearDown() {}

  void testLca() {
    RmqLca lca(9, 0);
    lca.addEdge(0, 2);
    lca.addEdge(2, 5);
    lca.addEdge(2, 3);
    lca.addEdge(0, 1);
    lca.addEdge(1, 6);
    lca.addEdge(1, 4);
    lca.addEdge(6, 7);
    lca.addEdge(6, 8);

    lca.build();

    CPPUNIT_ASSERT_EQUAL(1, lca.findLca(4, 7));
    CPPUNIT_ASSERT_EQUAL(6, lca.findLca(7, 8));
    CPPUNIT_ASSERT_EQUAL(2, lca.findLca(3, 5));
    CPPUNIT_ASSERT_EQUAL(1, lca.findLca(1, 7));
    CPPUNIT_ASSERT_EQUAL(0, lca.findLca(6, 3));
  }

  CPPUNIT_TEST_SUITE(RmqLcaTest);
  CPPUNIT_TEST(testLca);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(RmqLcaTest);
