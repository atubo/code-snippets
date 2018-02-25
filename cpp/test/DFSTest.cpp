#include <bits/stdc++.h>
using namespace std;

#include "Graph.h"
#include "DFS.cpp"

#include <boost/assign/list_of.hpp>

#include <cppunit/extensions/HelperMacros.h>

using namespace boost::assign;

class DFSTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testThreeNodeChain() {
        DFS dfs(3);
        dfs.addEdge(2, 1);
        dfs.addEdge(1, 2);
        dfs.addEdge(1, 0);
        dfs.addEdge(0, 1);

        dfs.dfs(2, -1);
        vector<int> dfn(dfs.dfn, dfs.dfn+3);
        vector<int> low(dfs.low, dfs.low+3);
        CPPUNIT_ASSERT(dfn == list_of(2)(1)(0));
        CPPUNIT_ASSERT(low == list_of(2)(1)(0));
    }

    void testThreeNodeTree() {
        DFS dfs(3);

        dfs.addEdge(0,2);
        dfs.addEdge(2,0);
        dfs.addEdge(0,1);
        dfs.addEdge(1,0);

        dfs.dfs(0, -1);

        vector<int> dfn(dfs.dfn, dfs.dfn+3);
        vector<int> low(dfs.low, dfs.low+3);
        CPPUNIT_ASSERT(dfn == list_of(0)(1)(2));
        CPPUNIT_ASSERT(low == list_of(0)(1)(2));
    }

    void testThreeNodeTriangle() {
        DFS dfs(3);
        dfs.addEdge(0,2);
        dfs.addEdge(2,0);
        dfs.addEdge(0,1);
        dfs.addEdge(1,0);
        dfs.addEdge(1,2);
        dfs.addEdge(2,1);

        dfs.dfs(0, -1);

        vector<int> dfn(dfs.dfn, dfs.dfn+3);
        vector<int> low(dfs.low, dfs.low+3);
        CPPUNIT_ASSERT(dfn == list_of(0)(1)(2));
        CPPUNIT_ASSERT(low == list_of(0)(0)(0));
    }

    CPPUNIT_TEST_SUITE(DFSTest);
    CPPUNIT_TEST(testThreeNodeChain);
    CPPUNIT_TEST(testThreeNodeTree);
    CPPUNIT_TEST(testThreeNodeTriangle);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(DFSTest);
