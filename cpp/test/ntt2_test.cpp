#include <bits/stdc++.h>

using namespace std;

#include "math/ntt2.h"

#include <cppunit/extensions/HelperMacros.h>

class Ntt2Test : public CppUnit::TestFixture {
 public:
  void setUp() {}
  void tearDown() {}

  void testConvolution() {
    const int p = 1004535809;
    Ntt2 ntt(p, 3, 8);
    int a[8] = {1, 2, 3, 4};
    int b[8] = {5, 6, 7, 8};
    ntt.ntt(a, 1, 8);
    ntt.ntt(b, 1, 8);
    for (int i = 0; i < 8; i++) {
      a[i] = 1LL * a[i] * b[i] % p;
    }
    ntt.ntt(a, -1, 8);
    int expected[8] = {5, 16, 34, 60, 61, 52, 32, 0};
    for (int i = 0; i < 8; i++) {
      CPPUNIT_ASSERT_EQUAL(expected[i], a[i]);
    }
  }

  void testInverse1() {
    Ntt2 ntt(998244353, 3, 8);
    int a[8] = {1, 998244351, 0, 0};
    int b[8] = {0};
    ntt.inverse(a, b, 4);
    int expected[8] = {1, 2, 4, 8, 0, 0, 0, 0};
    for (int i = 0; i < 8; i++) {
      CPPUNIT_ASSERT_EQUAL(expected[i], b[i]);
    }
  }

  void testInverse2() {
    Ntt2 ntt(998244353, 3, 16);
    int a[16] = {3, 4, 5, 1, 2};
    int b[16] = {0};
    ntt.inverse(a, b, 5);
    int expected[16] = {332748118,
      221832078, 480636170, 875004310, 398476140};
    for (int i = 0; i < 16; i++) {
      CPPUNIT_ASSERT_EQUAL(expected[i], b[i]);
    }
  }

  CPPUNIT_TEST_SUITE(Ntt2Test);
  CPPUNIT_TEST(testConvolution);
  CPPUNIT_TEST(testInverse1);
  CPPUNIT_TEST(testInverse2);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(Ntt2Test);
