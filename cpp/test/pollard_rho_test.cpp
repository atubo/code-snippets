#include <bits/stdc++.h>

using namespace std;

#include "math/miller_rabin.h"
#include "math/pollard_rho.h"

#include <cppunit/extensions/HelperMacros.h>

class PollardRhoTest : public CppUnit::TestFixture {
 public:
  void setUp() {}
  void tearDown() {}

  void test() {
    PollardRho pr;
    vector<int64_t> primes = {1787, 1913, 2423, 3539, 4409, 5023};
    for (int i = 0; i < (int)primes.size(); i++) {
      for (int j = i+1; j < (int)primes.size(); j++) {
        int64_t n = primes[i]*primes[j];
        auto ret = pr.factorize(n);
        CPPUNIT_ASSERT_EQUAL(2UL, ret.size());
        CPPUNIT_ASSERT_EQUAL(primes[i], ret[0]);
        CPPUNIT_ASSERT_EQUAL(primes[j], ret[1]);
      }
    }
  }

  CPPUNIT_TEST_SUITE(PollardRhoTest);
  CPPUNIT_TEST(test);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(PollardRhoTest);
