#include <bits/stdc++.h>

using namespace std;

#include "graph/tarjan_ebcc.h"

#include <cppunit/extensions/HelperMacros.h>

class TarjanEbccTest : public CppUnit:: TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testSolve() {
        TarjanEbcc bcc(10, 12);
        bcc.addEdge(0, 1);
        bcc.addEdge(1, 4);
        bcc.addEdge(1, 5);
        bcc.addEdge(4, 5);
        bcc.addEdge(0, 2);
        bcc.addEdge(2, 6);
        bcc.addEdge(2, 7);
        bcc.addEdge(6, 7);
        bcc.addEdge(0, 3);
        bcc.addEdge(3, 8);
        bcc.addEdge(3, 9);
        bcc.addEdge(8, 9);
        bcc.solve();

        vector<int> bcc_expected = {0, 1, 2, 3, 1, 1, 2, 2, 3, 3};
        for (int u = 0; u < 10; u++) {
            CPPUNIT_ASSERT_EQUAL(bcc_expected[u], bcc.bcc_[u]);
        }

        vector<vector<int>> adj(10);
        for (int u = 0; u < 10; u++) {
            for (int eidx = bcc.g_bcc_.head[u]; ~eidx;
                 eidx = bcc.g_bcc_.E[eidx].next) {
                int v = bcc.g_bcc_.E[eidx].to;
                adj[u].push_back(v);
            }
            sort(adj[u].begin(), adj[u].end());
        }

        CPPUNIT_ASSERT(adj[0].size() == 3);
        CPPUNIT_ASSERT(adj[0] == vector<int>({1, 2, 3}));
        CPPUNIT_ASSERT(adj[1].size() == 1 && adj[1][0] == 0);
        CPPUNIT_ASSERT(adj[2].size() == 1 && adj[2][0] == 0);
        CPPUNIT_ASSERT(adj[3].size() == 1 && adj[3][0] == 0);
        for (int u = 4; u < 10; u++) {
            CPPUNIT_ASSERT(adj[u].empty());
        }
    }

    CPPUNIT_TEST_SUITE(TarjanEbccTest);
    CPPUNIT_TEST(testSolve);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(TarjanEbccTest);
