#include <bits/stdc++.h>

using namespace std;

#include "string/sam_large_alphabet.h"

#include <cppunit/extensions/HelperMacros.h>

class SuffixAutomatonLargeAlphabetTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    bool checkSubstring(const SuffixAutomatonLargeAlphabet &sam,
                        const vector<int> &s) {
        SuffixAutomatonLargeAlphabet::Node *node = sam.start;
        for (int c: s) {
            if (!node->getCh(c)) return false;
            node = node->getCh(c);
        }
        return true;
    }

    void testBuild() {
        vector<int> s = {1, 2, 3, 1};
        SuffixAutomatonLargeAlphabet sam(4);
        sam.build(s);
        CPPUNIT_ASSERT(checkSubstring(sam, {1, 2, 3, 1}));
        CPPUNIT_ASSERT(checkSubstring(sam, {2, 3}));
        CPPUNIT_ASSERT(checkSubstring(sam, {1, 2}));
        CPPUNIT_ASSERT(!checkSubstring(sam, {1, 1}));
    }

    void testCalc() {
        vector<int> s = {1, 2, 1, 2, 3};
        SuffixAutomatonLargeAlphabet sam(5);
        sam.build(s);
        sam.calc();
        SuffixAutomatonLargeAlphabet::Node *node = sam.start;
        node = node->getCh(1);
        node = node->getCh(2);
        CPPUNIT_ASSERT_EQUAL(2, node->posCnt);
    }

    CPPUNIT_TEST_SUITE(SuffixAutomatonLargeAlphabetTest);
    CPPUNIT_TEST(testBuild);
    CPPUNIT_TEST(testCalc);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SuffixAutomatonLargeAlphabetTest);
