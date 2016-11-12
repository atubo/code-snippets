
#include "UnionFind.h"

class Kruskal {
    using TIII = tuple<int, int, int>;  // (weight, u, v)
    using Adj = vector<vector<int>>;
public:
    static Adj mst(vector<TIII>& edges, int N) {
        Adj adj(N);
        UnionFind uf(N);
        sort(edges.begin(), edges.end());
        for (const TIII& e: edges) {
            int w, u, v;
            tie(w, u, v) = e;
            if (uf.find(u) == uf.find(v)) continue;
            adj[u].push_back(v);
            adj[v].push_back(u);
            uf.join(u, v);
        }
        return adj;
    }
};
