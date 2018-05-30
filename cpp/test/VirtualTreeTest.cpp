#include <bits/stdc++.h>
using namespace std;

#include "VirtualTree.h"

#include <boost/assign/list_of.hpp>

#include <cppunit/extensions/HelperMacros.h>

using namespace boost::assign;

class VirtualTreeTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void addEdge(VirtualTree& t, int u, int v) {
        t.addEdge(u, v);
    }

    vector<int> getChildren(const VirtualTree::Graph &vg, int u) {
        vector<int> ret;
        for (int eidx = vg.head[u]; ~eidx; eidx = vg.E[eidx].next) {
            ret.push_back(vg.E[eidx].to);
        }
        return ret;
    }

    void testSingleNode() {
        VirtualTree t(1, 0);

        t.preCompute();
        vector<int> vertices = {0};
        int cnt = t.buildVirtualTree(vertices, 1);
        CPPUNIT_ASSERT_EQUAL(1, cnt);
        CPPUNIT_ASSERT_EQUAL(0, vertices[0]);
        CPPUNIT_ASSERT(getChildren(t.vg, 0).empty());
    }

    void testPartialNodes() {
        VirtualTree t(7, 0);
        addEdge(t, 0, 1);
        addEdge(t, 0, 2);
        addEdge(t, 1, 3);
        addEdge(t, 1, 4);
        addEdge(t, 2, 5);
        addEdge(t, 2, 6);

        t.preCompute();
        vector<int> vertices = {3, 4, -1, -1, -1, -1, -1};
        int cnt = t.buildVirtualTree(vertices, 2);

        CPPUNIT_ASSERT_EQUAL(3, cnt);
        CPPUNIT_ASSERT(vertices == list_of(4)(3)(1)(-1)(-1)(-1)(-1));

        auto c = getChildren(t.vg, 1);
        CPPUNIT_ASSERT(c == list_of(3)(4));
        CPPUNIT_ASSERT(getChildren(t.vg, 3).empty());
        CPPUNIT_ASSERT(getChildren(t.vg, 4).empty());


        vertices[2] = 2;    // now (3, 4, 2, ...)
        cnt = t.buildVirtualTree(vertices, 3);
        CPPUNIT_ASSERT_EQUAL(5, cnt);
        CPPUNIT_ASSERT(vertices == list_of(2)(4)(3)(0)(1)(-1)(-1));
        c = getChildren(t.vg, 0);
        CPPUNIT_ASSERT(c == list_of(1)(2));
        c = getChildren(t.vg, 1);
        CPPUNIT_ASSERT(c == list_of(3)(4));
        CPPUNIT_ASSERT(getChildren(t.vg, 2).empty());
        CPPUNIT_ASSERT(getChildren(t.vg, 3).empty());
        CPPUNIT_ASSERT(getChildren(t.vg, 4).empty());
    }

    CPPUNIT_TEST_SUITE(VirtualTreeTest);
    CPPUNIT_TEST(testSingleNode);
    CPPUNIT_TEST(testPartialNodes);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(VirtualTreeTest);
