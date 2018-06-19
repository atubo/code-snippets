#include <bits/stdc++.h>

using namespace std;

#include "ntt.h"

#include <cppunit/extensions/HelperMacros.h>

class NttTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testPrimeRoot() {
        CPPUNIT_ASSERT_EQUAL(2, Ntt::primeRoot(3));
        CPPUNIT_ASSERT_EQUAL(2, Ntt::primeRoot(11));
        CPPUNIT_ASSERT_EQUAL(5, Ntt::primeRoot(23));
    }

    void testConvolution() {
        vector<int> a(8), b(8);
        for (int i = 0; i < 4; i++) {
            a[i] = i+1;
            b[i] = i+5;
        }
        const int p = 1004535809, g = 3;
        vector<int> c = Ntt::conv(a, b, p, g);
        vector<int> expected = {5, 16, 34, 60, 61, 52, 32, 0};
        for (int i = 0; i < 8; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], c[i]);
        }
    }

    void testPolynomialInverse() {
        vector<int> a{3, 4, 5, 1, 2};
        auto b = Ntt::polynomialInverse(5, a, 998244353, 3);
        vector<int> expected = {332748118,
            221832078, 480636170, 875004310, 398476140};
        CPPUNIT_ASSERT(b.size() == 16);
        for (int i = 0; i < 5; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], b[i]);
        }
        for (int i = 5; i < 16; i++) {
            CPPUNIT_ASSERT_EQUAL(0, b[i]);
        }
    }

    void testBernoulli() {
        auto b = Ntt::bernoulli(1<<10, 1004535809, 3);
        CPPUNIT_ASSERT_EQUAL(1, b[0]);
        CPPUNIT_ASSERT_EQUAL(502267904, b[1]);
        CPPUNIT_ASSERT_EQUAL(167422635, b[2]);
        CPPUNIT_ASSERT_EQUAL(0, b[3]);
        CPPUNIT_ASSERT_EQUAL(971051282, b[4]);
        CPPUNIT_ASSERT_EQUAL(756407540, b[1022]);
        CPPUNIT_ASSERT_EQUAL(0, b[1023]);
    }

    CPPUNIT_TEST_SUITE(NttTest);
    CPPUNIT_TEST(testPrimeRoot);
    CPPUNIT_TEST(testConvolution);
    CPPUNIT_TEST(testPolynomialInverse);
    CPPUNIT_TEST(testBernoulli);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(NttTest);
