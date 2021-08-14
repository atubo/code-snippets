#include <bits/stdc++.h>

using namespace std;

#include "graph/tarjan_indirected_biconnected.h"

#include <cppunit/extensions/HelperMacros.h>

class TarjanIndirectedBccTest:public CppUnit::TestFixture {
 public:
  void setUp() {}
  void tearDown() {}

  void testSolve() {
    TarjanIndirectedBcc bcc(13, 15);
    bcc.addEdge(0, 1);
    bcc.addEdge(0, 6);
    bcc.addEdge(1, 2);
    bcc.addEdge(1, 3);
    bcc.addEdge(1, 5);
    bcc.addEdge(2, 3);
    bcc.addEdge(2, 4);
    bcc.addEdge(3, 4);
    bcc.addEdge(5, 6);
    bcc.addEdge(5, 7);
    bcc.addEdge(5, 8);
    bcc.addEdge(7, 8);
    bcc.addEdge(8, 9);
    bcc.addEdge(10, 11);
    bcc.addEdge(10, 12);

    bcc.solve();
    vector<bool> art_exp = {0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0};
    for (int i = 0; i < 13; i++) {
      CPPUNIT_ASSERT(bcc.art_[i] == art_exp[i]);
    }
    vector<int> belong_exp = {3, 3, 2, 2, 2, 3, 3, 1, 1, 0, 4, 4, 4};
    for (int i = 0; i < 13; i++) {
      CPPUNIT_ASSERT_EQUAL(belong_exp[i], bcc.belong_[i]);
    }
    set<int> art_belong_exp = {2, 3};
    CPPUNIT_ASSERT(bcc.art_belong_[1] == art_belong_exp);
    art_belong_exp = {1, 3};
    CPPUNIT_ASSERT(bcc.art_belong_[5] == art_belong_exp);
    art_belong_exp = {0, 1};
    CPPUNIT_ASSERT(bcc.art_belong_[8] == art_belong_exp);
    art_belong_exp = {4};
    CPPUNIT_ASSERT(bcc.art_belong_[10] == art_belong_exp);
  }


  CPPUNIT_TEST_SUITE(TarjanIndirectedBccTest);
  CPPUNIT_TEST(testSolve);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(TarjanIndirectedBccTest);
