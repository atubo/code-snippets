#include <bits/stdc++.h>
using namespace std;

#include "string/suffix_array.h"

#include <cppunit/extensions/HelperMacros.h>

class SuffixArrayTest:public CppUnit::TestFixture {
 public:
  void setUp() {}
  void tearDown() {}

  void testSingleCharString() {
    string s = "c";
    SuffixArray sa(s.c_str());
    sa.buildSA();
    CPPUNIT_ASSERT_EQUAL(sa.sa_[0], 0);
    CPPUNIT_ASSERT_EQUAL(sa.pos_[0], 0);
  }

  void testOneCharString() {
    string s = "aaa";

    SuffixArray sa(s.c_str());
    sa.buildSA();
    sa.buildLCP();

    CPPUNIT_ASSERT_EQUAL(sa.sa_[0], 2);
    CPPUNIT_ASSERT_EQUAL(sa.sa_[1], 1);
    CPPUNIT_ASSERT_EQUAL(sa.sa_[2], 0);

    CPPUNIT_ASSERT_EQUAL(sa.pos_[0], 2);
    CPPUNIT_ASSERT_EQUAL(sa.pos_[1], 1);
    CPPUNIT_ASSERT_EQUAL(sa.pos_[2], 0);

    CPPUNIT_ASSERT_EQUAL(sa.lcp_[0], 1);
    CPPUNIT_ASSERT_EQUAL(sa.lcp_[1], 2);
    CPPUNIT_ASSERT_EQUAL(sa.lcp_[2], 0);
  }

  void testShortString() {
    string s = "aba";

    SuffixArray sa(s.c_str());
    sa.buildSA();
    sa.buildLCP();
    CPPUNIT_ASSERT_EQUAL(sa.sa_[0], 2);
    CPPUNIT_ASSERT_EQUAL(sa.sa_[1], 0);
    CPPUNIT_ASSERT_EQUAL(sa.sa_[2], 1);

    CPPUNIT_ASSERT_EQUAL(sa.pos_[0], 1);
    CPPUNIT_ASSERT_EQUAL(sa.pos_[1], 2);
    CPPUNIT_ASSERT_EQUAL(sa.pos_[2], 0);

    CPPUNIT_ASSERT_EQUAL(sa.lcp_[0], 1);
    CPPUNIT_ASSERT_EQUAL(sa.lcp_[1], 0);
    CPPUNIT_ASSERT_EQUAL(sa.lcp_[2], 0);
  }

  void testPMatrix() {
    string s = "bobocel";
    SuffixArray sa(s.c_str());
    sa.buildSA();
    sa.buildLCP();

    int golden[4][7] = {
      {0, 4, 0, 4, 1, 2, 3},
      {0, 4, 0, 5, 1, 2, 3},
      {0, 5, 1, 6, 2, 3, 4},
      {0, 5, 1, 6, 2, 3, 4},
    };
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 7; j++) {
        CPPUNIT_ASSERT_EQUAL(golden[i][j], sa.p_[i][j]);
      }
    }

    sa.buildRMQ();
    CPPUNIT_ASSERT_EQUAL(2, sa.calcLCP(2, 0));
    CPPUNIT_ASSERT_EQUAL(1, sa.calcLCP(1, 3));
    CPPUNIT_ASSERT_EQUAL(0, sa.calcLCP(0, 6));
  }

  CPPUNIT_TEST_SUITE(SuffixArrayTest);
  CPPUNIT_TEST(testSingleCharString);
  CPPUNIT_TEST(testOneCharString);
  CPPUNIT_TEST(testShortString);
  CPPUNIT_TEST(testPMatrix);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SuffixArrayTest);


