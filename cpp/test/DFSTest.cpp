#include "Graph.cpp"
#include "DFS.cpp"

#include <iostream>

#include <boost/assign/list_of.hpp>

#include <cppunit/extensions/HelperMacros.h>

using namespace std;
using namespace boost::assign;

class DFSTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testThreeNodeChain() {
        Graph graph(3);
        graph.addEdge(2,1);
        graph.addEdge(1,0);

        vector<int> preorder;
        vector<int> postorder;
        auto pre = [&preorder](int v) {preorder.push_back(v);};
        auto post = [&postorder](int v) {postorder.push_back(v);};

        DFS::dfs(graph, 2, pre, post);

        CPPUNIT_ASSERT(preorder == list_of(2)(1)(0));
        CPPUNIT_ASSERT(postorder == list_of(0)(1)(2));
    }

    void testThreeNodeTree() {
        Graph graph(3);
        graph.addEdge(0,1);
        graph.addEdge(0,2);

        vector<int> preorder;
        vector<int> postorder;
        auto pre = [&preorder](int v) {preorder.push_back(v);};
        auto post = [&postorder](int v) {postorder.push_back(v);};

        DFS::dfs(graph, 0, pre, post);

        CPPUNIT_ASSERT(preorder == list_of(0)(1)(2));
        CPPUNIT_ASSERT(postorder == list_of(1)(2)(0));
    }

    void testThreeNodeTriangle() {
        Graph graph(3);
        graph.addEdge(0,1);
        graph.addEdge(1,2);
        graph.addEdge(0,2);

        vector<int> preorder;
        vector<int> postorder;
        auto pre = [&preorder](int v) {preorder.push_back(v);};
        auto post = [&postorder](int v) {postorder.push_back(v);};

        DFS::dfs(graph, 0, pre, post);

        CPPUNIT_ASSERT(preorder == list_of(0)(1)(2));
        CPPUNIT_ASSERT(postorder == list_of(2)(1)(0));
    }

    CPPUNIT_TEST_SUITE(DFSTest);
    CPPUNIT_TEST(testThreeNodeChain);
    CPPUNIT_TEST(testThreeNodeTree);
    CPPUNIT_TEST(testThreeNodeTriangle);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(DFSTest);
