#include <bits/stdc++.h>

using namespace std;

#include "fft.h"

#include <cppunit/extensions/HelperMacros.h>

class FftTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testLength4() {
        // FFT of [1, 2, 3, 4]
        vector<double> data(8);
        for (int i = 0; i < 4; i++) data[2*i] = i+1;
        Fft::four1(data, 1);
        vector<double> expRe = {10, -2, -2, -2};
        vector<double> expIm = {0, -2, 0, 2};
        for (int i = 0; i < 4; i++) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(data[2*i], expRe[i], 1e-6);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(data[2*i+1], expIm[i], 1e-6);
        }
    }

    void testPolynomicalMultiplication() {
        // (1+2x+3x^2+4x^3)(5+6x+7x^2+8x^3)
        // answser should be 32x^6+52x^5+61x^4+60x^3+34x^2+16x+5
        vector<double> a(16), b(16);
        for (int i = 0; i < 4; i++) {
            a[2*i] = i+1;
            b[2*i] = i+5;
        }
        Fft::four1(a, 1);
        Fft::four1(b, 1);

        vector<double> c = Fft::innerProduct(a, b);
        Fft::four1(c, -1);
        vector<double> expected = {5, 16, 34, 60, 61, 52, 32, 0};
        for (int i = 0; i < 8; i++) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[i], c[2*i]/8, 1e-6);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(0, c[2*i+1], 1e-6);
        }
    }

    CPPUNIT_TEST_SUITE(FftTest);
    CPPUNIT_TEST(testLength4);
    CPPUNIT_TEST(testPolynomicalMultiplication);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(FftTest);
