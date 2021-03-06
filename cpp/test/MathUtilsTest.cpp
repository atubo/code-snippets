#include <bits/stdc++.h>
using namespace std;

#include "MathUtils.h"
#include "math/modular_utils.h"

#include <cppunit/extensions/HelperMacros.h>

#include <boost/assign/list_of.hpp>
using namespace boost::assign;

using namespace std;

class MathUtilsTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testXorUpto() {
        int64_t x = xorUpto(0);
        CPPUNIT_ASSERT_EQUAL(int64_t(0), x);

        x = xorUpto(1);
        CPPUNIT_ASSERT_EQUAL(int64_t(1), x);
        
        x = xorUpto(7);
        CPPUNIT_ASSERT_EQUAL(int64_t(0), x);

        x = xorUpto(8);
        CPPUNIT_ASSERT_EQUAL(int64_t(8), x);
    }

    void testGcd() {
        CPPUNIT_ASSERT_EQUAL(int64_t(1), ModularUtils::gcd(4, 5));
        CPPUNIT_ASSERT_EQUAL(int64_t(2), ModularUtils::gcd(2, 4));
        CPPUNIT_ASSERT_EQUAL(int64_t(7), ModularUtils::gcd(28, 21));
        CPPUNIT_ASSERT_EQUAL(int64_t(1), ModularUtils::gcd(1, 5));
    }

    void testCountOnes() {
        int64_t x = countOnes(0);
        CPPUNIT_ASSERT_EQUAL(int64_t(0), x);

        x = countOnes(1);
        CPPUNIT_ASSERT_EQUAL(int64_t(1), x);

        x = countOnes(4);
        CPPUNIT_ASSERT_EQUAL(int64_t(5), x);

        x = countOnes(9);
        CPPUNIT_ASSERT_EQUAL(int64_t(15), x);
    }

    void testBinom() {
        Binom::generate(20);
        for (int i = 0; i <= 20; i++) {
            CPPUNIT_ASSERT_EQUAL(1, Binom::binom[i][0]);
            CPPUNIT_ASSERT_EQUAL(1, Binom::binom[i][i]);
        }
        CPPUNIT_ASSERT_EQUAL(21, Binom::binom[7][2]);
        CPPUNIT_ASSERT_EQUAL(21, Binom::binom[7][5]);
        CPPUNIT_ASSERT_EQUAL(1140, Binom::binom[20][3]);
    }

    void testModSolve() {
        CPPUNIT_ASSERT_EQUAL(int64_t(2), ModularUtils::mod_solve(4, 1, 7));
        CPPUNIT_ASSERT_EQUAL(int64_t(3), ModularUtils::mod_solve(5, 1, 7));
        CPPUNIT_ASSERT_EQUAL(int64_t(7), ModularUtils::mod_solve(6, 2, 8));
    }

    void testModSolveLargeInt() {
        int64_t x = ModularUtils::mod_solve(34891, 2695824305, 15753131385);
        CPPUNIT_ASSERT_EQUAL(5287090205L, x);
    }

    void testPhi() {
        vector<int64_t> expected = list_of(0)( 1)(1)( 2)(2)(4)(2)( 6)(4)(6)
            (4)(10)(4)(12)(6)(8)(8)(16)(6)(18)(8);
        for (int i = 1; i <= 20; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], phi(i));
        }

        CPPUNIT_ASSERT_EQUAL(int64_t(2147483646), phi(4294967294));
    }


    CPPUNIT_TEST_SUITE(MathUtilsTest);
    CPPUNIT_TEST(testXorUpto);
    CPPUNIT_TEST(testGcd);
    CPPUNIT_TEST(testCountOnes);
    CPPUNIT_TEST(testBinom);
    CPPUNIT_TEST(testModSolve);
    CPPUNIT_TEST(testModSolveLargeInt);
    CPPUNIT_TEST(testPhi);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MathUtilsTest);
