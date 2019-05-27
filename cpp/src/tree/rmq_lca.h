// Online algorithm, pre-computing O(N log N)
// Each query O(1)

class RmqLca {
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

    int N_, root_;
    int MAXB_;
    Graph g_;

    int *log_;
    int *dfn_;  // node to first time in euler tour array
    int *depth_;
    int** st_;
    int dfs_clock_ = 0;

public:
    RmqLca(int N, int root)
        : N_(N), root_(root), MAXB_(log2(N)+1), g_(N, 2*(N-1)) {
            alloc();
    }

    ~RmqLca() {
        dealloc();
    }

    void addEdge(int u, int v) {
        g_.addEdge(u, v);
        g_.addEdge(v, u);
    }

    void build() {
        dfs(root_, -1, 0);

        setSparseTable();
    }

    int findLca(int u, int v) const {
        int x = dfn_[u], y = dfn_[v];
        if (x > y) swap(x, y);
        int d = log_[y-x+1];
        int a = st_[x][d], b = st_[y-(1<<d)+1][d];
        int lca = depth_[a] < depth_[b] ? a : b;
        return lca;
    }

private:
    void alloc() {
        log_ = new int[2*N_]{};
        dfn_ = new int[N_]{};
        depth_ = new int[N_]{};
        st_ = new int*[2*N_]{};
        for (int i = 0; i < 2*N_; i++) {
            st_[i] = new int[MAXB_]{};
            memset(st_[i], -1, MAXB_*sizeof(int));
        }
    }

    void dealloc() {
        delete[] log_;
        delete[] dfn_;
        delete[] depth_;
        for (int i = 0; i < 2*N_; i++) {
            delete[] st_[i];
        }
        delete[] st_;
    }

    void dfs(int x, int f, int d) {
        dfn_[x] = dfs_clock_;
        depth_[x] = d;
        st_[dfs_clock_++][0] = x;
        for (int eidx = g_.head[x]; ~eidx; eidx = g_.E[eidx].next) {
            int u = g_.E[eidx].to;
            if (u != f) {
                dfs(u, x, d+1);
                st_[dfs_clock_++][0] = x;
            }
        }
    }

    void setSparseTable() {
        for (int i = 2; i < dfs_clock_; i++) {
            log_[i] = log_[i>>1] + 1;
        }
        for (int j = 1; j < MAXB_; j++) {
            for (int i = 0; i <= dfs_clock_-(1<<j); i++) {
                int x = st_[i][j-1], y = st_[i+(1<<(j-1))][j-1];
                st_[i][j] = depth_[x] < depth_[y] ? x : y;
            }
        }
    }
};
