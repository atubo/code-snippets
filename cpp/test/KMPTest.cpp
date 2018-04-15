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
        for (int i = 0; i < 9; i++) {
            printf("%d ", kmp[i]);
        }
        printf("\n");
    }

    CPPUNIT_TEST_SUITE(KMPTest);
    CPPUNIT_TEST(testPrefixFunction);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(KMPTest);
