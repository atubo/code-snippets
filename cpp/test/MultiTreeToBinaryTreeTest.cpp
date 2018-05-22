#include <bits/stdc++.h>

using namespace std;

#include "MultiTreeToBinaryTree.h"

#include <cppunit/extensions/HelperMacros.h>

class MultiTreeToBinaryTreeTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testBuild() {
        using Node = MultiTreeToBinaryTree::Node;
        vector<vector<int>> children(8);
        children[0] = {1, 2, 3};
        children[1] = {4, 5, 6};
        children[2] = {7};
        MultiTreeToBinaryTree bt(children, 0);

        CPPUNIT_ASSERT(bt.nodes[0] == Node(1, -1));
        CPPUNIT_ASSERT(bt.nodes[1] == Node(4, 3));
        CPPUNIT_ASSERT(bt.nodes[2] == Node(7, -1));
        CPPUNIT_ASSERT(bt.nodes[3] == Node(-1, 2));
        CPPUNIT_ASSERT(bt.nodes[4] == Node(-1, 6));
        CPPUNIT_ASSERT(bt.nodes[5] == Node(-1, -1));
        CPPUNIT_ASSERT(bt.nodes[6] == Node(-1, 5));
        CPPUNIT_ASSERT(bt.nodes[7] == Node(-1, -1));
    }

    CPPUNIT_TEST_SUITE(MultiTreeToBinaryTreeTest);
    CPPUNIT_TEST(testBuild);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MultiTreeToBinaryTreeTest);
