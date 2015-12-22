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

    void testPMatrix() {
        string s = "bobocel";

        SuffixArray::S = s.c_str();
        SuffixArray::buildSA();
        SuffixArray::buildLCP();

        int golden[5][7] = {
            {0, 4, 0, 4, 1, 2, 3},
            {0, 4, 0, 5, 1, 2, 3},
            {0, 5, 1, 6, 2, 3, 4},
            {0, 5, 1, 6, 2, 3, 4},
            {0, 5, 1, 6, 2, 3, 4},
        };
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 7; j++) {
                CPPUNIT_ASSERT_EQUAL(golden[i][j], SuffixArray::P[i][j]);
            }
        }
        
        CPPUNIT_ASSERT_EQUAL(2, SuffixArray::calcLCP(2, 0));
        CPPUNIT_ASSERT_EQUAL(1, SuffixArray::calcLCP(1, 3));
        CPPUNIT_ASSERT_EQUAL(0, SuffixArray::calcLCP(0, 6));
    }

    CPPUNIT_TEST_SUITE(SuffixArrayTest);
    CPPUNIT_TEST(testOneCharString);
    CPPUNIT_TEST(testShortString);
    CPPUNIT_TEST(testPMatrix);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SuffixArrayTest);


