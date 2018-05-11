#include <bits/stdc++.h>

using namespace std;

#include "DfsOrder.h"

#include <boost/assign/list_of.hpp>

#include <cppunit/extensions/HelperMacros.h>

using namespace boost::assign;

class DfsOrderTest : public CppUnit::TestFixture {
private:
    void addEdge(Graph &g, int u, int v) {
        g.addEdge(u, v);
        g.addEdge(v, u);
    }
public:
    void setUp() {}
    void tearDown() {}

    void testDfn() {
        Graph g(6, 10);
        addEdge(g, 0, 1);
        addEdge(g, 0, 2);
        addEdge(g, 0, 3);
        addEdge(g, 2, 4);
        addEdge(g, 2, 5);

        DfsOrder dfn;
        dfn.dfs(g, 0, -1);
        CPPUNIT_ASSERT(dfn.A == list_of(0)(3)(3)(2)(5)(5)(4)(4)(2)(1)(1)(0));
        vector<int> first, last;
        for (int i = 0; i < 6; i++) {
            first.push_back(dfn.first[i]);
            last.push_back(dfn.last[i]);
        }
        CPPUNIT_ASSERT(first == list_of(0)(9)(3)(1)(6)(4));
        CPPUNIT_ASSERT(last  == list_of(11)(10)(8)(2)(7)(5));
    }

    CPPUNIT_TEST_SUITE(DfsOrderTest);
    CPPUNIT_TEST(testDfn);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(DfsOrderTest);
