#include <bits/stdc++.h>

using namespace std;

#include "BinaryTrie.h"

#include <cppunit/extensions/HelperMacros.h>

class BinaryTrieTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testBinaryTrie() {
        BinaryTrie trie(2);
        trie.insert(0);
        trie.insert(1);
        trie.insert(3);
        trie.insert(3);

        CPPUNIT_ASSERT(trie.root->count == 4);
        CPPUNIT_ASSERT(trie.root->children[0]->count == 2);
        CPPUNIT_ASSERT(trie.root->children[0]->children[0]->count == 1);
        CPPUNIT_ASSERT(trie.root->children[0]->children[1]->count == 1);
        CPPUNIT_ASSERT(trie.root->children[1]->count == 2);
        CPPUNIT_ASSERT(trie.root->children[1]->children[0] == NULL);
        CPPUNIT_ASSERT(trie.root->children[1]->children[1]->count == 2);
    }

    CPPUNIT_TEST_SUITE(BinaryTrieTest);
    CPPUNIT_TEST(testBinaryTrie);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(BinaryTrieTest);
