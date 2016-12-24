#include <bits/stdc++.h>
using namespace std;

#include "BigInt.h"

#include <cppunit/extensions/HelperMacros.h>

class BigIntTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testSub() {
        CPPUNIT_ASSERT(BigInt::sub("123", "45") == "78");
        CPPUNIT_ASSERT(BigInt::sub("123", "123") == "0");
    }

    void testAdd() {
        CPPUNIT_ASSERT(BigInt::add("123", "987") == "1110");
        CPPUNIT_ASSERT(BigInt::add("999", "1") == "1000");
    }

    void testMod() {
        CPPUNIT_ASSERT(BigInt::mod("12", "13") == "12");
        CPPUNIT_ASSERT(BigInt::mod("13", "12") == "1");
        CPPUNIT_ASSERT(BigInt::mod("24", "12") == "0");
        CPPUNIT_ASSERT(BigInt::mod("100", "12") == "4");
    }

    CPPUNIT_TEST_SUITE(BigIntTest);
    CPPUNIT_TEST(testSub);
    CPPUNIT_TEST(testAdd);
    CPPUNIT_TEST(testMod);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(BigIntTest);
