#include <bits/stdc++.h>
using namespace std;

#include "BigInt.h"

#include <cppunit/extensions/HelperMacros.h>

class BigIntStringReprTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testToBinary() {
        CPPUNIT_ASSERT(BigIntStringRepr::toBinary("19") == "10011");
        CPPUNIT_ASSERT(BigIntStringRepr::toBinary("1024") == "10000000000");
    }

    void testSub() {
        CPPUNIT_ASSERT(BigIntStringRepr::sub("123", "45") == "78");
        CPPUNIT_ASSERT(BigIntStringRepr::sub("123", "123") == "0");
    }

    void testAdd() {
        CPPUNIT_ASSERT(BigIntStringRepr::add("123", "987") == "1110");
        CPPUNIT_ASSERT(BigIntStringRepr::add("999", "1") == "1000");
    }

    void testMod() {
        CPPUNIT_ASSERT(BigIntStringRepr::mod("12", "13") == "12");
        CPPUNIT_ASSERT(BigIntStringRepr::mod("13", "12") == "1");
        CPPUNIT_ASSERT(BigIntStringRepr::mod("24", "12") == "0");
        CPPUNIT_ASSERT(BigIntStringRepr::mod("100", "12") == "4");
    }

    CPPUNIT_TEST_SUITE(BigIntStringReprTest);
    CPPUNIT_TEST(testToBinary);
    CPPUNIT_TEST(testSub);
    CPPUNIT_TEST(testAdd);
    CPPUNIT_TEST(testMod);
    CPPUNIT_TEST_SUITE_END();
};

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

    CPPUNIT_TEST_SUITE(BigIntTest);
    CPPUNIT_TEST(testSub);
    CPPUNIT_TEST(testAdd);
    CPPUNIT_TEST(testMul);
    CPPUNIT_TEST(testMod);
    CPPUNIT_TEST(testToString);
    CPPUNIT_TEST(testSwap);
    CPPUNIT_TEST_SUITE_END();
};


CPPUNIT_TEST_SUITE_REGISTRATION(BigIntStringReprTest);
CPPUNIT_TEST_SUITE_REGISTRATION(BigIntTest);
