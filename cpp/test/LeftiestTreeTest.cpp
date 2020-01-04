#include <bits/stdc++.h>

using namespace std;

#include "LeftistTree.h"

#include <cppunit/extensions/HelperMacros.h>

class LeftistTreeTest:public CppUnit::TestFixture {
 public:
  void setUp() {}
  void tearDown() {}

  void testOneTree() {
    LeftistTree<> lt(5);
    int root = lt.push(0, 1, 3);
    root = lt.push(root, 2, 1);
    root = lt.push(root, 3, 5);
    CPPUNIT_ASSERT(check(lt,
          {0, 2, 0, 2, 0, 0},
          {{0, 0}, {0, 0}, {1, 3}, {0, 0}, {0, 0}, {0, 0}},
          {0, 3, 1, 5,  0, 0},
          {-1, 0, 1, 0, -1, -1}));

    root = lt.push(root, 4, 4);
    root = lt.push(root, 5, 2);
    CPPUNIT_ASSERT(check(lt,
          {0, 2, 0, 4, 5, 2},
          {{0, 0}, {0, 0}, {1, 5}, {0, 0}, {3, 0}, {4, 0}},
          {0, 3, 1, 5, 4, 2},
          {-1, 0, 1, 0, 0, 0}));

    vector<int> result;
    for (int i = 0; i < 5; i++) {
      result.push_back(lt.top(root));
      root = lt.pop(root);
    }
    vector<int> expected = {1, 2, 3, 4, 5};
    CPPUNIT_ASSERT(result == expected);
  }

  void testMergeTwoTrees() {
    LeftistTree<> lt(8);
    int root = lt.push(0, 1, 6);
    root = lt.push(root, 2, 2);
    root = lt.push(root, 3, 10);
    root = lt.push(root, 4, 8);
    root = lt.push(root, 5, 4);
    CPPUNIT_ASSERT_EQUAL(2, root);

    root = lt.push(0, 6, 5);
    root = lt.push(root, 7, 7);
    root = lt.push(root, 8, 3);
    CPPUNIT_ASSERT_EQUAL(8, root);
    CPPUNIT_ASSERT(check(lt,
          {0, 2, 0, 4, 5, 2, 8, 6, 0},
          {{0, 0}, {0, 0}, {1, 5}, {0, 0}, {3, 0}, {4, 0},
          {7, 0}, {0, 0}, {6, 0}},
          {0, 6, 2, 10, 8, 4, 5, 7, 3},
          {-1, 0, 1, 0, 0, 0, 0, 0, 0}));

    root = lt.merge(8, 2);
    CPPUNIT_ASSERT_EQUAL(2, root);
    CPPUNIT_ASSERT(check(lt,
          {0, 2, 0, 4, 5, 8, 8, 6, 2},
          {{0, 0}, {0, 0}, {8, 1}, {0, 0}, {3, 0}, {4, 0},
          {7, 0}, {0, 0}, {6, 5}},
          {0, 6, 2, 10, 8, 4, 5, 7, 3},
          {-1, 0, 1, 0, 0, 0, 0, 0, 1}));

    vector<int> result;
    for (int i = 0; i < 8; i++) {
      result.push_back(lt.top(root));
      root = lt.pop(root);
    }
    vector<int> expected = {2, 3, 4, 5, 6, 7, 8, 10};
  }

  void testUpdateNode() {
    LeftistTree<> lt(5);
    int root = lt.push(0, 1, 1);
    for (int i = 2; i <= 5; i++) {
      root = lt.push(root, i, i);
    }
    CPPUNIT_ASSERT_EQUAL(1, lt.top(root));
    root = lt.update(1, 6);
    CPPUNIT_ASSERT_EQUAL(2, lt.top(root));
  }


 private:
  bool check(const LeftistTree<> &lt,
      const vector<int> &f,
      const vector<array<int, 2>> &t,
      const vector<int> &val,
      const vector<int> &d) {
    int n = f.size();
    for (int i = 0; i < n; i++) {
      if (f[i] != lt.f[i] ||
          t[i][0] != lt.t[i][0] || t[i][1] != lt.t[i][1] ||
          val[i] != lt.val[i] ||
          d[i] != lt.d[i]) {
        return false;
      }
    }
    return true;
  } 


  CPPUNIT_TEST_SUITE(LeftistTreeTest);
  CPPUNIT_TEST(testOneTree);
  CPPUNIT_TEST(testMergeTwoTrees);
  CPPUNIT_TEST(testUpdateNode);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(LeftistTreeTest);
