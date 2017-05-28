#include <bits/stdc++.h>

using namespace std;

#include "SplayTree.h"

#include <cppunit/extensions/HelperMacros.h>

class SplayTreeTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testBuild() {
        SplayTree st(5);
        CPPUNIT_ASSERT(check(st, {0, 3, 1, 0, 3, 4},
                             {{0, 0}, {0, 2}, {0, 0}, {1, 4}, {0, 5}, {0, 0}},
                             {0, 2, 1, 5, 2, 1},
                             {0, 0, 0, 0, 0, 0},
                             3));
    }

    void testSplay() {
        SplayTree st(5);
        st.splay(5, 0);

        CPPUNIT_ASSERT(check(st,
                             {0, 3, 1, 4, 5, 0},
                             {{0, 0}, {0, 2}, {0, 0}, {1, 0}, {3, 0}, {4, 0}},
                             {0, 2, 1, 3, 4, 5},
                             {0, 0, 0, 0, 0, 0},
                             5));
    }

    void testReverseAndSplay() {
        SplayTree st(5);
        st.reverse(1);
        st.splay(1, 0);

        CPPUNIT_ASSERT(check(st,
                             {0, 0, 1, 1, 3, 4},
                             {{0, 0}, {2, 3}, {0, 0}, {0, 4}, {0, 5}, {0, 0}},
                             {0, 5, 1, 3, 2, 1},
                             {0, 0, 1, 0, 0, 0},
                             1));
    }

    void testFindByOrder() {
        SplayTree st(5);
        for (int i = 1; i <= 5; i++) {
            CPPUNIT_ASSERT_EQUAL(i, st.find_by_order(i));
        }
        st.reverse(3);
        vector<int> expected = {0, 5, 4, 3, 2, 1};
        for (int i = 1; i <= 5; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], st.find_by_order(i));
        }
    }

private:
    bool check(const SplayTree &st,
               const vector<int> &f,
               const vector<array<int, 2>> &t,
               const vector<int> &sz,
               const vector<int> tag,
               int root) {
        return f == st.f && t == st.t && sz == st.sz && tag == st.tag &&
           root == st.root;
    } 

    CPPUNIT_TEST_SUITE(SplayTreeTest);
    CPPUNIT_TEST(testBuild);
    CPPUNIT_TEST(testSplay);
    CPPUNIT_TEST(testReverseAndSplay);
    CPPUNIT_TEST(testFindByOrder);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SplayTreeTest);
