#include "Trie.cpp"

#include <boost/assign/list_of.hpp>

#include <cppunit/extensions/HelperMacros.h>

using namespace boost::assign;

class FullBinaryTrieTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testTraverse() {
        FullBinaryTrie<int> trie(3);
        FullBinaryTrie<int>::Iterator it = trie.root();
        *it = 1;
        *it.goLeft() = 2;
        *it.goUp().goRight() = 3;
        *it.goUp().goLeft().goLeft() = 4;
        *it.goUp().goRight() = 5;
        *it.goUp().goUp().goRight().goLeft() = 6;
        *it.goUp().goRight() = 7;

        CPPUNIT_ASSERT(trie.data == list_of(0)(1)(2)(3)(4)(5)(6)(7));
    }

    CPPUNIT_TEST_SUITE(FullBinaryTrieTest);
    CPPUNIT_TEST(testTraverse);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(FullBinaryTrieTest);

