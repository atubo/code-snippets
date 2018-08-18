#include <bits/stdc++.h>

using namespace std;

#include "Hungarian.h"
#include "graph/bipartite_min_vertex_cover.h"

#include <cppunit/extensions/HelperMacros.h>

class BipartiteMinVertexCoverTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testCalcMinVertexCover() {
        Hungarian hungarian(4, 5);
        hungarian.addEdge(0, 2);
        hungarian.addEdge(1, 0);
        hungarian.addEdge(1, 1);
        hungarian.addEdge(1, 3);
        hungarian.addEdge(2, 2);
        hungarian.addEdge(3, 2);
        hungarian.addEdge(3, 3);
        hungarian.addEdge(3, 3);
        int max_match = hungarian.maxMatch();
        CPPUNIT_ASSERT_EQUAL(3, max_match);
        auto match = hungarian.getMatch();
        BipartiteMinVertexCover bmc(match.nx, match.ny,
                                    match.cx, match.cy, match.g);
        auto vc = bmc.calcMinVertexCover();
        vector<int> expected = {1, 3, 6};
        CPPUNIT_ASSERT(vc == expected);
    }

    CPPUNIT_TEST_SUITE(BipartiteMinVertexCoverTest);
    CPPUNIT_TEST(testCalcMinVertexCover);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(BipartiteMinVertexCoverTest);
