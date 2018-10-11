#include <bits/stdc++.h>

using namespace std;

#include "graph/steiner_tree.h"

#include <cppunit/extensions/HelperMacros.h>

class SteinerTreeTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        SteinerTree::Graph g(4, 6);
        g.addEdge(0, 1, 8);
        g.addEdge(0, 2, 10);
        g.addEdge(1, 2, 6);
        g.addEdge(0, 3, 5);
        g.addEdge(1, 3, 5);
        g.addEdge(2, 3, 5);
        vector<int> terminals = {0, 1, 2};
        SteinerTree st(g, terminals);
        st.solve();
        vector<int> expected = {14, 14, 14, 15};
        for (int i = 0; i < 4; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], st.f_[i][7]);
        }
    }

    CPPUNIT_TEST_SUITE(SteinerTreeTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SteinerTreeTest);

