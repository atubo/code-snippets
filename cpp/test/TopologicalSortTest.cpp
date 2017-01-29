#include <bits/stdc++.h>
using namespace std;

#include "TopologicalSort.h"

#include <cppunit/extensions/HelperMacros.h>

class TopologicalSortTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void addEdge(TopologicalSort& t, int u, int v) {
        t.adj[u].push_back(v);
    }

    void testSort() {
        TopologicalSort t;
        t.N = 10;
        t.adj.resize(t.N);

        addEdge(t, 0, 9);
        addEdge(t, 2, 9);
        addEdge(t, 6, 7);
        addEdge(t, 5, 7);
        addEdge(t, 6, 3);
        addEdge(t, 8, 3);
        addEdge(t, 6, 5);
        addEdge(t, 4, 7);
        addEdge(t, 0, 7);
        addEdge(t, 1, 7);

        t.sort();

        vector<int> pos(10);
        for (int i = 0; i < 10; i++) {
            pos[t.topo[i]] = i;
        }

        // make sure the order is right by comparing
        // pos of a node and its succ
        for (int u = 0; u < 10; u++) {
            for (int v: t.adj[u]) {
                CPPUNIT_ASSERT(pos[u] < pos[v]);
            }
        }
    }

    CPPUNIT_TEST_SUITE(TopologicalSortTest);
    CPPUNIT_TEST(testSort);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(TopologicalSortTest);
