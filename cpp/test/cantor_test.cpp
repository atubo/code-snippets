#include <bits/stdc++.h>

using namespace std;

#include "math/cantor.h"

#include <cppunit/extensions/HelperMacros.h>

namespace math {

class CantorTest : public CppUnit::TestFixture {
 public:
  void setUp() {}
  void tearDown() {}

  void testEncode() {
    CPPUNIT_ASSERT_EQUAL(98884L, Cantor::encode({2,4,6,3,0,1,8,5,7}));
  }

  void testDecode() {
    auto ret = Cantor::decode(95, 5);
    CPPUNIT_ASSERT(ret == vector<int>({3, 4, 2, 1, 0}));

    ret = Cantor::decode(98884, 9);
    CPPUNIT_ASSERT(ret == vector<int>({2,4,6,3,0,1,8,5,7}));
  }

  CPPUNIT_TEST_SUITE(CantorTest);
  CPPUNIT_TEST(testEncode);
  CPPUNIT_TEST(testDecode);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(CantorTest);
}

