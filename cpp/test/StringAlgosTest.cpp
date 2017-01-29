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
        CPPUNIT_ASSERT_EQUAL(9LL, result);

        result = numCommonSubsequences("ab", "aba");
        CPPUNIT_ASSERT_EQUAL(4LL, result);
    }

    CPPUNIT_TEST_SUITE(StringAlgosTest);
    CPPUNIT_TEST(testNumCommonSubsequences);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(StringAlgosTest);

