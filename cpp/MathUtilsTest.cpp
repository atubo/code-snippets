#include <bits/stdc++.h>
using namespace std;

#include "MathUtils.h"

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
        CPPUNIT_ASSERT_EQUAL(0LL, x);

        x = xorUpto(1);
        CPPUNIT_ASSERT_EQUAL(1LL, x);
        
        x = xorUpto(7);
        CPPUNIT_ASSERT_EQUAL(0LL, x);

        x = xorUpto(8);
        CPPUNIT_ASSERT_EQUAL(8LL, x);
    }

    void testCountOnes() {
        int64_t x = countOnes(0);
        CPPUNIT_ASSERT_EQUAL(0LL, x);

        x = countOnes(1);
        CPPUNIT_ASSERT_EQUAL(1LL, x);

        x = countOnes(4);
        CPPUNIT_ASSERT_EQUAL(5LL, x);

        x = countOnes(9);
        CPPUNIT_ASSERT_EQUAL(15LL, x);
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
        CPPUNIT_ASSERT_EQUAL(2LL, mod_solve(4, 1, 7));
        CPPUNIT_ASSERT_EQUAL(3LL, mod_solve(5, 1, 7));
        CPPUNIT_ASSERT_EQUAL(7LL, mod_solve(6, 2, 8));
    }

    void testPhi() {
        vector<int64_t> expected = list_of(0)( 1)(1)( 2)(2)(4)(2)( 6)(4)(6)
            (4)(10)(4)(12)(6)(8)(8)(16)(6)(18)(8);
        for (int i = 1; i <= 20; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], phi(i));
        }
    }


    CPPUNIT_TEST_SUITE(MathUtilsTest);
    CPPUNIT_TEST(testXorUpto);
    CPPUNIT_TEST(testCountOnes);
    CPPUNIT_TEST(testBinom);
    CPPUNIT_TEST(testModSolve);
    CPPUNIT_TEST(testPhi);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MathUtilsTest);
