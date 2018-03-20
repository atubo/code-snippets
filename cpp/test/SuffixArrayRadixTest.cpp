#include <bits/stdc++.h>

using namespace std;

#include "SuffixArrayRadix.h"

#include <boost/assign/list_of.hpp>
#include <cppunit/extensions/HelperMacros.h>

using namespace boost::assign;

class SuffixArrayRadixTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testBuildSA() {
        SuffixArrayRadix sa("banana`");
        sa.buildSA();
        vector<int> actual;
        for (int i = 0; i < 7; i++) {
            actual.push_back(sa.sa[i]);
        }
        vector<int> expected = list_of(6)(5)(3)(1)(0)(4)(2);
        CPPUNIT_ASSERT(actual == expected);
    }

    void testBuildLCP() {
        SuffixArrayRadix sa("banana`");
        sa.buildSA();
        sa.buildLCP();
        vector<int> actual;
        for (int i = 0; i < 7; i++) {
            actual.push_back(sa.lcp[i]);
        }
        vector<int> expected = list_of(0)(1)(3)(0)(0)(2)(0);
        CPPUNIT_ASSERT(actual == expected);
    }

    CPPUNIT_TEST_SUITE(SuffixArrayRadixTest);
    CPPUNIT_TEST(testBuildSA);
    CPPUNIT_TEST(testBuildLCP);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SuffixArrayRadixTest);
