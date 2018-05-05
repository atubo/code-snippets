#include <bits/stdc++.h>

using namespace std;

#include "PalindromicTree.h"

#include <cppunit/extensions/HelperMacros.h>

class PalindromicTreeTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testConstruct() {
        const string s = "abbaabba";
        PalindromicTree pt(s);
        vector<int> expected = {1, 0, 0, 0, 3, 2, 2, 3, 4, 5};
        for (int i = 0; i < 10; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], pt.fail[i]);
        }

        expected = {0, -1, 1, 1, 2, 4, 2, 4, 6, 8};
        for (int i = 0; i < 10; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], pt.len[i]);
        }

        expected = {8, 8, 4, 4, 2, 2, 1, 1, 1, 1};
        for (int i = 0; i < 10; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], pt.cnt[i]);
        }

        expected = {0, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int i = 0; i < 9; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], pt.node[i]);
        }
    }

    CPPUNIT_TEST_SUITE(PalindromicTreeTest);
    CPPUNIT_TEST(testConstruct);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(PalindromicTreeTest);
