
class VirtualTree {
public:
    // Note graph node is 0-indexed
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


    vector<pair<int, int> > vEdges;

private:
    int MAXB_;
    int sz_;
    int N_, root_;
    vector<int> depth_;
    vector<vector<int> > father_;
    vector<int> dfn_;
    vector<int> stk_;

    Graph g_;

public:
    VirtualTree(int n, int r): N_(n), root_(r), g_(n, n-1) {
        MAXB_ = int(log2(N_) + 1.5);
        sz_ = 0;
    }

    // only father to child edges are allowed
    void addEdge(int u, int v) {
        g_.addEdge(u, v);
    }

    void preCompute() {

        depth_.resize(N_);
        father_.resize(N_);
        dfn_.resize(N_);
        for (int i = 0; i < N_; i++) {
            father_[i].resize(MAXB_, -1);
        }

        dfs(root_, root_, 0);

        binaryLift();

        stk_.resize(N_);
    }

    void dfs(int x, int f, int d) {
        dfn_[x] = sz_++;
        depth_[x] = d;
        father_[x][0] = f;
        for (int eidx = g_.head[x]; ~eidx; eidx = g_.E[eidx].next) {
            int u = g_.E[eidx].to;
            if (u != f) dfs(u, x, d+1);
        }
    }

    void binaryLift() {
        for (int j = 1; j < MAXB_; j++) {
            for (int i = 0; i < N_; i++) {
                if (father_[i][j-1] != -1) {
                    father_[i][j] = father_[father_[i][j-1]][j-1];
                }
            }
        }
    }

    int findLCA(int u, int v) {
        if (depth_[u] < depth_[v]) swap(u, v);
        for (int b = MAXB_-1; b >= 0; b--) {
            if (father_[u][b] == -1) continue;
            if (depth_[father_[u][b]] >= depth_[v]) {
                u = father_[u][b];
            }
        }

        if (u == v) return u;

        for (int b = MAXB_-1; b >= 0; b--) {
            if (father_[u][b] == -1) continue;
            if (father_[u][b] != father_[v][b]) {
                u = father_[u][b];
                v = father_[v][b];
            }
        }
        return father_[u][0];
    }

    struct CmpByDfn {
        CmpByDfn(const VirtualTree& t): m_t(t) {}
        const VirtualTree& m_t;

        bool operator()(int i, int j) {
            return m_t.dfn_[i] < m_t.dfn_[j];
        }
    };

    int buildVirtualTree(vector<int>& vertices, int k) {
        vEdges.clear();

        sz_ = 0;
        int cnt = k;
        sort(vertices.begin(), vertices.begin()+k, CmpByDfn(*this));

        for (int i = 0; i < k; i++) {
            int u = vertices[i];
            int lca = (sz_ > 0 ? findLCA(u, stk_[sz_-1]) : u);
            if (sz_ == 0 || lca == stk_[sz_-1]) stk_[sz_++] = u;
            else {
                while (sz_ - 2 >= 0 && depth_[stk_[sz_-2]] >= depth_[lca]) {
                    addVirtualEdge(stk_[sz_-2], stk_[sz_-1]);
                    sz_--;
                }

                if (stk_[sz_-1] != lca) {
                    addVirtualEdge(lca, stk_[--sz_]);
                    stk_[sz_++] = lca;
                    vertices[cnt++] = lca;
                }

                stk_[sz_++] = u;
            }
        }

        for (int i = 0; i < sz_-1; i++) {
            addVirtualEdge(stk_[i], stk_[i+1]);
        }

        sort(vEdges.begin(), vEdges.end());
        return cnt;
    }

    void addVirtualEdge(int u, int v) {
        vEdges.push_back(make_pair(u, v));
    }
};
