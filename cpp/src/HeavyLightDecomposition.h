
#include "SegmentTreeTD.h"

class HeavyLightDecomposition {
private:
    // Note graph node is 0-indexed
    class Graph {
    public:
        struct Edge {
            int next, to;
        };

        vector<int> head;
        int eidx;
        int N;

        Edge *E;

        Graph(int N_):N(N_) {
            head.resize(N);
            eidx = 0;

            for (int i = 0; i < N; i++) {
                head[i] = -1;
            }

            // since this should be a tree
            E = new Edge[2*N-2]{};
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
    const int N;
    Graph g;
    vector<int> size;
    vector<int> dep;
    vector<int> rev;    // node to father-edge
    vector<int> heavy;
    vector<int> num;    // edge to segment tree index
    vector<int> fa;
    vector<int> top;
    int root;
    int Seg_size;
    SegmentTreeTD<int> *st;

    HeavyLightDecomposition(int N_): N(N_), g(N_) {
        size.resize(N);
        dep.resize(N);
        rev.resize(N);
        heavy.resize(N);
        num.resize(2*N, -1);
        fa.resize(N);
        top.resize(N);

        root = 0;
        Seg_size = 0;
    }

    void addEdge(int u, int v) {
        g.addEdge(u, v);
        g.addEdge(v, u);
    }

    ~HeavyLightDecomposition() {
        delete st;
        st = NULL;
    }

    void dfs1(int u, int f) {
        int mx = -1, e = -1;
        size[u] = 1;

        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (v == f) continue;
            dep[v] = dep[u] + 1;
            rev[v] = eidx ^ 1;
            dfs1(v, u);
            size[u] += size[v];
            if (size[v] > mx) {
                mx = size[v];
                e = eidx;
            }
        }
        heavy[u] = e;
        if (e != -1) fa[g.E[e].to] = u;
    }

    void dfs2(int u, int f) {
        if (heavy[u] != -1) {
            int t = heavy[u];
            num[t^1] = Seg_size++;
            int v = g.E[t].to;
            top[v] = top[u];
            dfs2(v, u);
        }

        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (v == f || eidx == heavy[u]) continue;
            num[eidx^1] = Seg_size++;
            top[v] = v;
            dfs2(v, u);
        }
    }

    void decompose() {
        // set up segment tree
        vector<int> A(N-1, 1);
        auto comb = [](int x, int y) {return x + y;};
        auto accu = [](int x, int y) {return x + y;};
        auto appl = [](int x, int d, int sz) {return x + d * sz;};
        st = new SegmentTreeTD<int>(A, 0, 0, comb, accu, appl);

        dfs1(root, root);
        top[root] = root;
        dfs2(root, root);
    }

    void updateChain(int u, int anc, int val) {
        while (u != anc) {
            int fe = rev[u];
            if (top[u] != u) {
                int p = top[u];
                if (dep[p] < dep[anc]) p = anc;
                int l = num[heavy[p]^1];
                int r = num[fe];
                st->update(l, r, val);
                u = p;
            } else {
                int r = num[fe];
                st->update(r, r, val);
                u = g.E[fe].to;
            }
        }
    }


    void update(int u, int v, int d) {
        int p = lca(u, v);;
        updateChain(u, p, d);
        updateChain(v, p, d);

        // if it's node update, update p related information here
    }

    int lca(int u, int v) {
        while (true) {
            int a = top[u], b = top[v];
            if (a == b) return dep[u] < dep[v] ? u : v;
            else if (dep[a] >= dep[b]) u = g.E[rev[a]].to;
            else v = g.E[rev[b]].to;
        }
    }
};
