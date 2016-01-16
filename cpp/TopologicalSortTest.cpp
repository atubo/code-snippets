#include "DirectedGraph.cpp"
#include "TopologicalSort.cpp"

#include <iostream>

#include <cppunit/extensions/HelperMacros.h>

using namespace std;

class TopologicalSortTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testSort() {
        DirectedGraph g(10);
        g.addEdge(0, 9);
        g.addEdge(2, 9);
        g.addEdge(6, 7);
        g.addEdge(5, 7);
        g.addEdge(6, 3);
        g.addEdge(8, 3);
        g.addEdge(6, 5);
        g.addEdge(4, 7);
        g.addEdge(0, 7);
        g.addEdge(1, 7);

        vector<int> topo = TopologicalSort::sort(g);
        vector<int> pos(10);
        for (int i = 0; i < 10; i++) {
            pos[topo[i]] = i;
        }

        // make sure the order is right by comparing
        // pos of a node and its succ
        for (int u = 0; u < 10; u++) {
            const vector<int>& succ = g.outNodes(u);
            for (int v: succ) {
                CPPUNIT_ASSERT(pos[u] < pos[v]);
            }
        }
    }

    CPPUNIT_TEST_SUITE(TopologicalSortTest);
    CPPUNIT_TEST(testSort);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(TopologicalSortTest);
