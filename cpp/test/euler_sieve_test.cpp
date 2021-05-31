#include <bits/stdc++.h>
using namespace std;

#include "math/euler_sieve.h"

#include <cppunit/extensions/HelperMacros.h>

#include <boost/assign/list_of.hpp>
using namespace boost::assign;

class EulerSieveTest:public CppUnit::TestFixture {
 public:
  void setUp() {}
  void tearDown() {}

  void testSieve() {
    EulerSieve sieve(20);
    CPPUNIT_ASSERT(sieve.primes == list_of(2)(3)(5)(7)(11)(13)(17)(19));
    //                                  0                5
    CPPUNIT_ASSERT(sieve.phi == list_of(0)( 1)(1)( 2)(2)(4)(2)( 6)(4)(6)
        (4)(10)(4)(12)(6)(8)(8)(16)(6)(18)(8));

    //                                  0                5
    CPPUNIT_ASSERT(sieve.mu == list_of(0)(1)(-1)(-1)(0)(-1)(1)(-1)(0)(0)
        (1)(-1)(0)(-1)(1)(1)(0)(-1)(0)(-1)(0));

    //                                    0              5
    CPPUNIT_ASSERT(sieve.sigma == list_of(0)(1)(3)(4)(7)(6)(12)(8)(15)(13)
        (18)(12)(28)(14)(24)
        (24)(31)(18)(39)(20)(42));
  }

  CPPUNIT_TEST_SUITE(EulerSieveTest);
  CPPUNIT_TEST(testSieve);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(EulerSieveTest);

