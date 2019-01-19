#include <bits/stdc++.h>
using namespace std;

#include "math/BigInt.h"

#include <cppunit/extensions/HelperMacros.h>

class BigIntTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testSub() {
        CPPUNIT_ASSERT(BigInt("123") - BigInt("45") == BigInt("78"));
        CPPUNIT_ASSERT(BigInt("123") - BigInt("123") == BigInt("0"));
        CPPUNIT_ASSERT(BigInt("987654321123456789") - BigInt("123456789987654321")
                       == BigInt("864197531135802468"));
        CPPUNIT_ASSERT(BigInt("987654321123456789") - BigInt("987654321123456789")
                       == BigInt("0"));
    }

    void testAdd() {
        CPPUNIT_ASSERT(BigInt("123") + BigInt("987") == BigInt("1110"));
        CPPUNIT_ASSERT(BigInt("999999999") + BigInt("1") == BigInt("1000000000"));
    }

    void testMul() {
        CPPUNIT_ASSERT(BigInt("3") * BigInt("4") == BigInt("12"));
        CPPUNIT_ASSERT(BigInt("12345678987654321") * BigInt("98765432123456789")
                       == BigInt("1219326320073159566072245112635269"));
    }

    void testDiv() {
        CPPUNIT_ASSERT(BigInt("122157167408911087668698763497987")/8932668 ==
            BigInt("13675328290373165964379148"));
    }

    void testMod() {
        CPPUNIT_ASSERT(BigInt("12") % BigInt("13") == BigInt("12"));
        CPPUNIT_ASSERT(BigInt("13") % BigInt("12") == BigInt("1"));
        CPPUNIT_ASSERT(BigInt("24") % BigInt("12") == BigInt("0"));
        CPPUNIT_ASSERT(BigInt("100") % BigInt("12") == BigInt("4"));
        CPPUNIT_ASSERT(BigInt("77777777777777") % BigInt("1257386185646")
                       == BigInt("1077220453371"));
    }

    void testToString() {
        CPPUNIT_ASSERT(BigInt("0").toString() == "0");
        CPPUNIT_ASSERT(BigInt("123").toString() == "123");
        CPPUNIT_ASSERT(BigInt("12345678987654321").toString() == "12345678987654321");
        CPPUNIT_ASSERT(BigInt("1234567000000000123456789").toString() ==
                       "1234567000000000123456789");
    }

    void testSwap() {
        BigInt a("123"), b("456");
        a.swap(b);
        CPPUNIT_ASSERT(a == BigInt("456"));
        CPPUNIT_ASSERT(b == BigInt("123"));
    }

    void testFromStringWithLeadingZeros() {
        BigInt a("0105752977");
        BigInt b("769539048420");
        BigInt c = a * b;
        CPPUNIT_ASSERT(c == BigInt("81381045288162146340"));
    }

    CPPUNIT_TEST_SUITE(BigIntTest);
    CPPUNIT_TEST(testSub);
    CPPUNIT_TEST(testAdd);
    CPPUNIT_TEST(testMul);
    CPPUNIT_TEST(testDiv);
    CPPUNIT_TEST(testMod);
    CPPUNIT_TEST(testToString);
    CPPUNIT_TEST(testSwap);
    CPPUNIT_TEST(testFromStringWithLeadingZeros);
    CPPUNIT_TEST_SUITE_END();
};


CPPUNIT_TEST_SUITE_REGISTRATION(BigIntTest);
