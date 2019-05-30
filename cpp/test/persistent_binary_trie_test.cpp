#include <bits/stdc++.h>

using namespace std;

#include "data_structures/persistent_binary_trie.h"

#include <cppunit/extensions/HelperMacros.h>

class PersistentBinaryTrieTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        PersistentBinaryTrie trie(5, 2);
        trie.insert(1, 0, 1);
        trie.insert(2, 1, 2);
        trie.insert(3, 2, 3);
        trie.insert(4, 3, 2);
        trie.insert(5, 4, 1);

        CPPUNIT_ASSERT_EQUAL(1, trie.query(3, 3));
        CPPUNIT_ASSERT_EQUAL(1, trie.query(2, 2));
        CPPUNIT_ASSERT_EQUAL(2, trie.query(4, 2));
        CPPUNIT_ASSERT_EQUAL(1, trie.query(1, 1));
        CPPUNIT_ASSERT_EQUAL(2, trie.query(5, 1));
        CPPUNIT_ASSERT_EQUAL(1, trie.query(5, 3));
        CPPUNIT_ASSERT_EQUAL(0, trie.query(5, 0));
    }

    CPPUNIT_TEST_SUITE(PersistentBinaryTrieTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(PersistentBinaryTrieTest);
