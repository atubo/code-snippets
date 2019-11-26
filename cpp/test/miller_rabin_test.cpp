#include <bits/stdc++.h>

using namespace std;

#include "math/miller_rabin.h"

#include <cppunit/extensions/HelperMacros.h>

class MillerRabinTest : public CppUnit::TestFixture {
 public:
  void setUp() {}
  void tearDown() {}

  void test() {
    MillerRabin millerRabin(20, 1);
    vector<int64_t> primes = {2, 3, 5, 19, 8191, 131071, 524287, 6700417,
      2147483647L, 67280421310721L};
    for (int64_t p : primes) {
      CPPUNIT_ASSERT(millerRabin.check(p));
    }

    primes = {1787, 1913, 2423, 3539, 4409, 5023};
    for (int i = 0; i < (int)primes.size(); i++) {
      for (int j = i+1; j < (int)primes.size(); j++) {
        CPPUNIT_ASSERT(!millerRabin.check(primes[i]*primes[j]));
      }
    }
  }

  CPPUNIT_TEST_SUITE(MillerRabinTest);
  CPPUNIT_TEST(test);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MillerRabinTest);
