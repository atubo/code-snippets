#include "StringAlgos.cpp"

#include <iostream>

#include <cppunit/extensions/HelperMacros.h>

using namespace std;

class StringAlgosTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testNumCommonSubsequences() {
        int64_t result = numCommonSubsequences("aaa", "aa");
        CPPUNIT_ASSERT_EQUAL(int64_t(9), result);

        result = numCommonSubsequences("ab", "aba");
        CPPUNIT_ASSERT_EQUAL(int64_t(4), result);
    }

    CPPUNIT_TEST_SUITE(StringAlgosTest);
    CPPUNIT_TEST(testNumCommonSubsequences);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(StringAlgosTest);

