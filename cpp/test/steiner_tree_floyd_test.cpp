#include <bits/stdc++.h>

using namespace std;

#include "graph/steiner_tree_floyd.h"

#include <cppunit/extensions/HelperMacros.h>

class SteinerTreeFloydTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        vector<int> terminals = {0, 1, 2};
        SteinerTreeFloyd steiner(4, terminals);
        steiner.addEdge(0, 1, 8);
        steiner.addEdge(0, 2, 10);
        steiner.addEdge(1, 2, 6);
        steiner.addEdge(0, 3, 5);
        steiner.addEdge(1, 3, 5);
        steiner.addEdge(2, 3, 5);
        steiner.solve();
        vector<int> expected = {14, 14, 14, 15};
        for (int i = 0; i < 4; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], steiner.dp[7][i]);
        }
    }

    CPPUNIT_TEST_SUITE(SteinerTreeFloydTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SteinerTreeFloydTest);
