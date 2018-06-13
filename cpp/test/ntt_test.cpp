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

    CPPUNIT_TEST_SUITE(NttTest);
    CPPUNIT_TEST(testPrimeRoot);
    CPPUNIT_TEST(testConvolution);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(NttTest);
