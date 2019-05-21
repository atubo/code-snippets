
class GravityTree {
public:
    struct Dist {
        int f;
        int64_t dist;
        int br;

        bool operator == (const Dist &other) const {
            return f == other.f &&
                dist == other.dist &&
                br == other.br;
        }
    };

    struct Edge {
        int to;
        int wt;
    };

    GravityTree(int n): fa_(n), n_(n), out_edges_(n) {
        alloc();
    }

    ~GravityTree() {
        dealloc();
    }

    void solve(int u) {
        dfs1(u, -1);
        if (sz_[u] == 1) {
            cut_[u] = true;
            fa_[u].push_back({u, 0, -1});
            return;
        }

        tot_ = sz_[u];
        miv_ = INF;
        dfs2(u, -1);
        cut_[rt_] = true;
        fa_[rt_].push_back({rt_, 0, -1});

        for (int i = 0; i < (int)out_edges_[rt_].size(); i++) {
            int v = out_edges_[rt_][i].to;
            int w = out_edges_[rt_][i].wt;
            if (cut_[v]) continue;
            dep_[v] = w;
            dfs3(v, rt_, rt_, i);
        }
        for (const auto &e: out_edges_[rt_]) {
            int v = e.to;
            if (!cut_[v]) solve(v);
        }
    }

    void addEdge(int u, int v, int w) {
        out_edges_[u].push_back({v, w});
        out_edges_[v].push_back({u, w});
    }

    vector<vector<Dist>> fa_;
private:
    static const int INF = 0x3F3F3F3F;
    const int n_;
    vector<vector<Edge>> out_edges_;
    int *sz_;
    bool *cut_;
    int tot_;
    int miv_;
    int rt_;
    int *dep_;

    void alloc() {
        sz_ = new int[n_]{};
        cut_ = new bool[n_]{};
        dep_ = new int[n_]{};
    }

    void dealloc() {
        delete[] sz_;
        delete[] cut_;
        delete[] dep_;
    }

    void dfs1(int u, int f) {
        sz_[u] = 1;
        for (const auto &e: out_edges_[u]) {
            if (e.to != f && !cut_[u]) {
                dfs1(e.to, u);
                sz_[u] += sz_[e.to];
            }
        }
    }

    void dfs2(int u, int f) {
        int mav = tot_ - sz_[u];
        for (const auto &e: out_edges_[u]) {
            int v = e.to;
            if (v != f && !cut_[v]) {
                dfs2(v, u);
                mav = max(mav, sz_[v]);
            }
        }
        if (miv_ > mav) {
            miv_ = mav;
            rt_ = u;
        }
    }

    void dfs3(int u, int f, int g, int br) {
        // f is the father on the original tree
        // g is the father on the gravity tree
        // br is the branch number on the gravity tree
        fa_[u].push_back({g, dep_[u], br});
        for (const auto &e: out_edges_[u]) {
            int v = e.to;
            int w = e.wt;
            if (v != f && !cut_[v]) {
                dep_[v] = dep_[u] + w;
                dfs3(v, u, g, br);
            }
        }
    }
};
