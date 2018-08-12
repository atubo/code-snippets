#include <bits/stdc++.h>

using namespace std;

#include "math/binom.h"

#include <cppunit/extensions/HelperMacros.h>

class BinomModuloPrimeTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        math::BinomModuloPrime binom(100, 1000000007);
        int x = binom.calc(37);
        CPPUNIT_ASSERT_EQUAL(26617247, x);
        x = binom.calc(100);
        CPPUNIT_ASSERT_EQUAL(1, x);
        x = binom.calc(200);
        CPPUNIT_ASSERT_EQUAL(0, x);
    }

    CPPUNIT_TEST_SUITE(BinomModuloPrimeTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

class BinomLucasTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        math::BinomLucas lucas(13);
        int x = lucas.lucas(100, 21);
        CPPUNIT_ASSERT_EQUAL(11, x);
        x = lucas.lucas(100, 23);
        CPPUNIT_ASSERT_EQUAL(0, x);
        x = lucas.lucas(100, 91);
        CPPUNIT_ASSERT_EQUAL(1, x);
        x = lucas.lucas(100, 95);
        CPPUNIT_ASSERT_EQUAL(9, x);
        x = lucas.lucas(100, 100);
        CPPUNIT_ASSERT_EQUAL(1, x);
        x = lucas.lucas(100, 200);
        CPPUNIT_ASSERT_EQUAL(0, x);
    }

    CPPUNIT_TEST_SUITE(BinomLucasTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(BinomModuloPrimeTest);
CPPUNIT_TEST_SUITE_REGISTRATION(BinomLucasTest);
