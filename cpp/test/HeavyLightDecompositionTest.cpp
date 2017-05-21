#include <bits/stdc++.h>

using namespace std;

#include "HeavyLightDecomposition.h"

#include <boost/assign/list_of.hpp>

#include <cppunit/extensions/HelperMacros.h>

using namespace boost::assign;

class HLDTest: public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testPrepare() {
        Graph g(14);
        
        addEdge(g, 0, 1);
        addEdge(g, 1, 4);
        addEdge(g, 1, 5);
        addEdge(g, 5, 10);
        addEdge(g, 5, 11);
        addEdge(g, 0, 2);
        addEdge(g, 2, 6);
        addEdge(g, 0, 3);
        addEdge(g, 3, 7);
        addEdge(g, 3, 8);
        addEdge(g, 8, 12);
        addEdge(g, 12, 13);
        addEdge(g, 3, 9);

        HeavyLightDecomposition hld(g);

        CPPUNIT_ASSERT(hld.Seg_size == 13);

        vector<int> result;
        for (int i = 0; i < 13; i++) {
            result.push_back(hld.num[2*i+1]);
        }
        vector<int> expected = {8, 12, 9, 11, 10, 6, 7, 0, 5, 1, 2, 3, 4};
        CPPUNIT_ASSERT(expected == result);

        expected = {0, 1, 2, 0, 4, 1, 2, 7, 0, 9, 10, 1, 0, 0};
        CPPUNIT_ASSERT(expected == hld.top);
    }

    void testUpdate() {
        Graph g(14);
        
        addEdge(g, 0, 1);
        addEdge(g, 1, 4);
        addEdge(g, 1, 5);
        addEdge(g, 5, 10);
        addEdge(g, 5, 11);
        addEdge(g, 0, 2);
        addEdge(g, 2, 6);
        addEdge(g, 0, 3);
        addEdge(g, 3, 7);
        addEdge(g, 3, 8);
        addEdge(g, 8, 12);
        addEdge(g, 12, 13);
        addEdge(g, 3, 9);

        HeavyLightDecomposition hld(g);
        hld.update(2, 12, 1);
        hld.update(7, 13, 2);
        hld.update(0, 10, 3);

        vector<int> result(13);
        for (int i = 0; i < 13; i++) {
            result[i] = hld.st->query(i, i);
        }
        vector<int> expected = {2, 4, 4, 3, 1, 3, 2, 1, 4, 4, 1, 4, 1};
        CPPUNIT_ASSERT(expected ==  result);
    }

    CPPUNIT_TEST_SUITE(HLDTest);
    CPPUNIT_TEST(testPrepare);
    CPPUNIT_TEST(testUpdate);
    CPPUNIT_TEST_SUITE_END();

private:
    void addEdge(Graph &g, int u, int v) {
        g.addEdge(u, v);
        g.addEdge(v, u);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(HLDTest);
