#include <bits/stdc++.h>

using namespace std;

#include "math/modular_utils.h"
#include "math/ext_chinese_remainder.h"

#include <cppunit/extensions/HelperMacros.h>

class ExtChineseRemainderTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testSolve() {
        ExtChineseRemainder ecr;
        bool ok = ecr.add(23, 84);
        CPPUNIT_ASSERT(ok);
        ok = ecr.add(7, 160);
        CPPUNIT_ASSERT(ok);
        ok = ecr.add(2, 63);
        CPPUNIT_ASSERT(ok);
    }

    void testNoSolution() {
        ExtChineseRemainder ecr;
        bool ok = ecr.add(3, 6);
        CPPUNIT_ASSERT(ok);
        ok = ecr.add(4, 10);
        CPPUNIT_ASSERT(!ok);
    }

    CPPUNIT_TEST_SUITE(ExtChineseRemainderTest);
    CPPUNIT_TEST(testSolve);
    CPPUNIT_TEST(testNoSolution);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ExtChineseRemainderTest);
