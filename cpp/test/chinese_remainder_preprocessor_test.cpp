#include <bits/stdc++.h>

using namespace std;

#include "math/chinese_remainder_preprocessor.h"

#include <cppunit/extensions/HelperMacros.h>

class ChineseRemainderPreprossorTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testProcess() {
        ChineseRemainderPreprocessor crp(3);
        crp.setRemainder(0, 23);
        crp.setRemainder(1, 7);
        crp.setRemainder(2, 2);
        crp.addModFactor(0, 2, 2);
        crp.addModFactor(0, 3, 1);
        crp.addModFactor(0, 7, 1);
        crp.addModFactor(1, 2, 5);
        crp.addModFactor(1, 5, 1);
        crp.addModFactor(2, 3, 2);
        crp.addModFactor(2, 7, 1);
        bool ok = crp.process();
        CPPUNIT_ASSERT(ok);

        CPPUNIT_ASSERT_EQUAL(4, (int)crp.equ.size());
        CPPUNIT_ASSERT_EQUAL(int64_t(7), crp.equ[0].r);
        CPPUNIT_ASSERT_EQUAL(int64_t(32), crp.equ[0].modulus);
        CPPUNIT_ASSERT_EQUAL(int64_t(2), crp.equ[1].r);
        CPPUNIT_ASSERT_EQUAL(int64_t(9), crp.equ[1].modulus);
        CPPUNIT_ASSERT_EQUAL(int64_t(2), crp.equ[2].r);
        CPPUNIT_ASSERT_EQUAL(int64_t(5), crp.equ[2].modulus);
        CPPUNIT_ASSERT_EQUAL(int64_t(2), crp.equ[3].r);
        CPPUNIT_ASSERT_EQUAL(int64_t(7), crp.equ[3].modulus);
    }

    void testProcessNoSolution() {
        ChineseRemainderPreprocessor crp(2);
        crp.setRemainder(0, 3);
        crp.setRemainder(1, 4);
        crp.addModFactor(0, 2, 1);
        crp.addModFactor(0, 3, 1);
        crp.addModFactor(1, 2, 1);
        crp.addModFactor(1, 5, 1);
        bool ok = crp.process();
        CPPUNIT_ASSERT(!ok);
    }

    CPPUNIT_TEST_SUITE(ChineseRemainderPreprossorTest);
    CPPUNIT_TEST(testProcess);
    CPPUNIT_TEST(testProcessNoSolution);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ChineseRemainderPreprossorTest);
