// generate DFS order for a tree
#include "Graph.h"

class DfsOrder {
public:
    static const int MAXN = 100010;
    vector<int> A;
    int first[MAXN], last[MAXN];
    int order;

    DfsOrder() {
        order = 0;
    }

    void dfs(const Graph &g, int u, int f) {
        first[u] = order++;
        A.push_back(u);
        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (v != f) dfs(g, v, u);
        }
        last[u] = order++;
        A.push_back(u);
    }
};
