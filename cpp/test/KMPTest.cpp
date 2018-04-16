#include <bits/stdc++.h>

using namespace std;

#include "KMP.h"

#include <cppunit/extensions/HelperMacros.h>

class KMPTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testPrefixFunction() {
        KMP kmp("abccababc");
        vector<int> expected = {0, 0, 0, 0, 1, 2, 1, 2, 3};
        for (int i = 0; i < 9; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], kmp[i]);
        }
    }

    CPPUNIT_TEST_SUITE(KMPTest);
    CPPUNIT_TEST(testPrefixFunction);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(KMPTest);
