#include "string/AhoCorasick.cpp"

#include <boost/assign/list_of.hpp>

#include <cppunit/extensions/HelperMacros.h>

using boost::assign::list_of;

class AhoCorasickTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testAhoCorasick() {

        AhoCorasick ac;
        ac.add_str(string("he"));
        ac.add_str(string("she"));
        ac.add_str(string("his"));
        ac.add_str(string("hers"));
        ac.push_links();

        CPPUNIT_ASSERT(ac.to[0]['s'] == 3);
        CPPUNIT_ASSERT(ac.to[2]['r'] == 8);
        CPPUNIT_ASSERT(ac.to[4]['e'] == 5);

        vector<int> link;
        link.assign(ac.link, ac.link+10);
        CPPUNIT_ASSERT(link == list_of(-1)(0)(0)(0)(1)(2)(0)(3)(0)(3));

        {
            // verify sizes of out
            vector<int> expectedSizes = list_of(0)(0)(1)(0)(0)(1)(0)(1)(0)(1);
            for (int i = 0; i < 10; i++) {
                CPPUNIT_ASSERT((int)ac.out[i].size() == expectedSizes[i]);
            }
        }

        CPPUNIT_ASSERT(ac.out[2] == list_of(0));   // matches "he" which is 1st
        CPPUNIT_ASSERT(ac.out[5] == list_of(1));
        CPPUNIT_ASSERT(ac.out[7] == list_of(2));
        CPPUNIT_ASSERT(ac.out[9] == list_of(3));

        CPPUNIT_ASSERT(ac.countTotalMatches("shershishe") == 6);
    }

    void testDictSuffixLink() {
        // as in https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm
        AhoCorasick ac;
        ac.add_str("a");
        ac.add_str("ab");
        ac.add_str("bab");
        ac.add_str("bc");
        ac.add_str("bca");
        ac.add_str("c");
        ac.add_str("caa");
        ac.push_links();
        vector<int> actual;
        for (int i = 0; i <= 10; i++) {
            actual.push_back(ac.next[i]);
        }
        vector<int> expected = list_of(0)(0)(0)(0)(1)(2)(8)(1)(0)(1)(1);
        CPPUNIT_ASSERT(actual == expected);
    }

    CPPUNIT_TEST_SUITE(AhoCorasickTest);
    CPPUNIT_TEST(testAhoCorasick);
    CPPUNIT_TEST(testDictSuffixLink);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(AhoCorasickTest);
