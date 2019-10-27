#include <bits/stdc++.h>

using namespace std;

#include "math/cantor.h"

#include <cppunit/extensions/HelperMacros.h>

namespace math {

class CantorTest : public CppUnit::TestFixture {
 public:
  void setUp() {}
  void tearDown() {}

  void testForward() {
    CPPUNIT_ASSERT_EQUAL(98884L, Cantor::forward({2,4,6,3,0,1,8,5,7}));
  }

  void testBackward() {
    auto ret = Cantor::backward(95, 5);
    CPPUNIT_ASSERT(ret == vector<int>({3, 4, 2, 1, 0}));

    ret = Cantor::backward(98884, 9);
    CPPUNIT_ASSERT(ret == vector<int>({2,4,6,3,0,1,8,5,7}));
  }

  CPPUNIT_TEST_SUITE(CantorTest);
  CPPUNIT_TEST(testForward);
  CPPUNIT_TEST(testBackward);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(CantorTest);
}

