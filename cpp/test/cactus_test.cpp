#include <bits/stdc++.h>

using namespace std;

#include "graph/cactus.h"

#include <cppunit/extensions/HelperMacros.h>

class CactusTest : public CppUnit::TestFixture {
 public:
  void setUp() {}
  void tearDown() {}

  void testQuery() {
    Cactus cactus(6, 6);
    cactus.addEdge(0, 1, 3);
    cactus.addEdge(1, 2, 2);
    cactus.addEdge(1, 3, 1);
    cactus.addEdge(2, 3, 4);
    cactus.addEdge(2, 4, 5);
    cactus.addEdge(3, 5, 6);
    cactus.build();

    CPPUNIT_ASSERT_EQUAL(14, cactus.query(4, 5));
    CPPUNIT_ASSERT_EQUAL(10, cactus.query(0, 4));
    CPPUNIT_ASSERT_EQUAL(7, cactus.query(1, 5));
  }

  CPPUNIT_TEST_SUITE(CactusTest);
  CPPUNIT_TEST(testQuery);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(CactusTest);
