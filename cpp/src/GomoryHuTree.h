// Gomory-Hu Tree (Cut Tree)

#include "Dinic.h"

class GomoryHuTree {
private:
    int N;
    Dinic dinic;
    int *vis;
    int *id;
    int currCompId;
public:
    vector<vector<pair<int, int64_t>>> edges;

    GomoryHuTree(int N_): N(N_), dinic(N_), currCompId(0) {
        alloc();
    }

    ~GomoryHuTree() {
        dealloc();
    }

    void addEdge(int u, int v, int w) {
        dinic.addEdge(u, v, w, w);
    }

    void build() {
        build(0, N-1);
    }
private:
    void alloc() {
        vis = new int[N];
        memset(vis, -1, N * sizeof(int));
        id  = new int[N];
        for (int i = 0; i < N; i++) {
            id[i] = i;
        }
        edges.resize(N);
    }

    void dealloc() {
        delete[] vis;
        delete[] id;
    }

    void build(int l, int r) {
        if (l >= r) return;
        vector<int> tmp(N);

        const int S = id[l], T = id[l+1];
        resetFlow();
        int64_t V = dinic.dinic(S, T);
        currCompId++;
        dfs(S);
        int p = l, q = r;
        for (int i = l; i <= r; i++) {
            if (vis[id[i]] == currCompId) tmp[p++] = id[i];
            else tmp[q--] = id[i];
        }
        edges[S].push_back(make_pair(T, V));
        edges[T].push_back(make_pair(S, V));
        for (int i = l; i <= r; i++) id[i] = tmp[i];
        build(l, p - 1);
        build(q + 1, r);
    }

    void dfs(int x) {
        vis[x] = currCompId;
        for (int eidx = dinic.head[x]; ~eidx; eidx = dinic.E[eidx].next) {
            int v = dinic.E[eidx].to;
            int c = dinic.E[eidx].cap;
            if (c && vis[v] != currCompId) {
                dfs(v);
            }
        }
    }

    void resetFlow() {
        for (int e = 0; e < dinic.e; e += 2) {
            int c1 = dinic.E[e].cap;
            int c2 = dinic.E[e^1].cap;
            int c = (c1 + c2) / 2;
            dinic.E[e].cap = dinic.E[e^1].cap = c;
        }
    }
};
