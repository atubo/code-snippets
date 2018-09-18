#include <bits/stdc++.h>

using namespace std;

#include "string/esam.h"

#include <cppunit/extensions/HelperMacros.h>

class ExtendedSuffixAutomatonTest:public CppUnit::TestFixture {
    class Graph {
    public:
        struct Edge {
            int next, to;
        };

        vector<int> head;
        int eidx;
        int N, M;

        Edge *E;

        Graph(int N_, int M_):N(N_), M(M_) {
            head.resize(N);
            eidx = 0;

            for (int i = 0; i < N; i++) {
                head[i] = -1;
            }

            E = new Edge[M]{};
        }

        ~Graph() {
            delete[] E;
        }

        // assume 0-indexed and no duplication
        void addEdge(int u, int v) {
            E[eidx].to = v;
            E[eidx].next = head[u];
            head[u] = eidx++;
        }
    };
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        vector<int> val = {0, 2, 1, 2, 1, 0, 0};
        Graph g(7, 12);
        addEdge(g, 0, 1);
        addEdge(g, 2, 3);
        addEdge(g, 2, 4);
        addEdge(g, 3, 5);
        addEdge(g, 4, 6);
        addEdge(g, 1, 4);
        ExtendedSuffixAutomaton esam(21);
        dfs(0, -1, esam, g, val, esam.start);
        dfs(5, -1, esam, g, val, esam.start);
        dfs(6, -1, esam, g, val, esam.start);

        int ans = 0;
        for (auto p = esam.start+1; p != esam._curr; p++) {
            ans += p->maxlen - p->next->maxlen;
        }
        CPPUNIT_ASSERT_EQUAL(30, ans);
    }

private:
    void addEdge(Graph &g, int u, int v) {
        g.addEdge(u, v);
        g.addEdge(v, u);
    }

    void dfs(int u, int fa, ExtendedSuffixAutomaton &esam,
             const Graph &g,
             const vector<int> &val,
             ExtendedSuffixAutomaton::Node *p) {
        ExtendedSuffixAutomaton::Node *curr = esam.ins(p, val[u]);
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (v != fa) {
                dfs(v, u, esam, g, val, curr);
            }
        }
    }

    CPPUNIT_TEST_SUITE(ExtendedSuffixAutomatonTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ExtendedSuffixAutomatonTest);
