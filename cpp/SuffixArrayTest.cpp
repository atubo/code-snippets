#include "SuffixArray.cpp"

#include <cppunit/extensions/HelperMacros.h>

class SuffixArrayTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testOneCharString() {
        string s = "aaa";

        SuffixArray::S = s.c_str();
        SuffixArray::buildSA();
        SuffixArray::buildLCP();

        CPPUNIT_ASSERT_EQUAL(SuffixArray::sa[0], 2);
        CPPUNIT_ASSERT_EQUAL(SuffixArray::sa[1], 1);
        CPPUNIT_ASSERT_EQUAL(SuffixArray::sa[2], 0);

        CPPUNIT_ASSERT_EQUAL(SuffixArray::pos[0], 2);
        CPPUNIT_ASSERT_EQUAL(SuffixArray::pos[1], 1);
        CPPUNIT_ASSERT_EQUAL(SuffixArray::pos[2], 0);

        CPPUNIT_ASSERT_EQUAL(SuffixArray::lcp[0], 1);
        CPPUNIT_ASSERT_EQUAL(SuffixArray::lcp[1], 2);
        CPPUNIT_ASSERT_EQUAL(SuffixArray::lcp[2], 0);
    }

    void testShortString() {
        string s = "aba";

        SuffixArray::S = s.c_str();
        SuffixArray::buildSA();
        SuffixArray::buildLCP();

        CPPUNIT_ASSERT_EQUAL(SuffixArray::sa[0], 2);
        CPPUNIT_ASSERT_EQUAL(SuffixArray::sa[1], 0);
        CPPUNIT_ASSERT_EQUAL(SuffixArray::sa[2], 1);

        CPPUNIT_ASSERT_EQUAL(SuffixArray::pos[0], 1);
        CPPUNIT_ASSERT_EQUAL(SuffixArray::pos[1], 2);
        CPPUNIT_ASSERT_EQUAL(SuffixArray::pos[2], 0);

        CPPUNIT_ASSERT_EQUAL(SuffixArray::lcp[0], 1);
        CPPUNIT_ASSERT_EQUAL(SuffixArray::lcp[1], 0);
        CPPUNIT_ASSERT_EQUAL(SuffixArray::lcp[2], 0);
    }

    CPPUNIT_TEST_SUITE(SuffixArrayTest);
    CPPUNIT_TEST(testOneCharString);
    CPPUNIT_TEST(testShortString);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SuffixArrayTest);


