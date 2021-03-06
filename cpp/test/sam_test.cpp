#include <bits/stdc++.h>

using namespace std;

#include "string/sam.h"

#include <cppunit/extensions/HelperMacros.h>

class SuffixAutomatonTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    bool checkSubstring(const SuffixAutomaton &sam, const string &s) {
        SuffixAutomaton::Node *node = sam.start;
        for (char c: s) {
            if (!node->ch[c-'a']) return false;
            node = node->ch[c-'a'];
        }
        return true;
    }

    void testBuild() {
        string s = "abca";
        SuffixAutomaton sam(4);
        sam.build(s);
        CPPUNIT_ASSERT(checkSubstring(sam, "abca"));
        CPPUNIT_ASSERT(checkSubstring(sam, "bc"));
        CPPUNIT_ASSERT(checkSubstring(sam, "ab"));
        CPPUNIT_ASSERT(!checkSubstring(sam, "aa"));
    }

    void testCalc() {
        string s = "ababc";
        SuffixAutomaton sam(5);
        sam.build(s);
        sam.calc();
        SuffixAutomaton::Node *node = sam.start;
        node = node->ch[0];
        node = node->ch[1];
        CPPUNIT_ASSERT_EQUAL(2, node->posCnt);
    }

    CPPUNIT_TEST_SUITE(SuffixAutomatonTest);
    CPPUNIT_TEST(testBuild);
    CPPUNIT_TEST(testCalc);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SuffixAutomatonTest);
