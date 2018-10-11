
class SteinerTree {
    const static int INF = INT_MAX/3;
public:
    // Weighted undirected graph, 0-indexed
    class Graph {
    public:
        struct Edge {
            int next, to, wt;
        };

        vector<int> head;
        int eidx;
        int N, M;

        Edge *E;

        Graph(int N_, int M_):N(N_), M(2*M_) {
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

        void addEdge(int u, int v, int w) {
            addDirectedEdge(u, v, w);
            addDirectedEdge(v, u, w);
        }

    private:
        void addDirectedEdge(int u, int v, int w) {
            E[eidx].to = v;
            E[eidx].wt = w;
            E[eidx].next = head[u];
            head[u] = eidx++;
        }
    };

    SteinerTree(const Graph &g,
                const vector<int> &terminals) : g_(g), t_(terminals) {
        m_ = t_.size();
        n_ = g_.N;

        alloc();
    }

    ~SteinerTree() {
        dealloc();
    }

    void solve() {
        for (int i = 0; i < n_; i++) {
            for (int j = 0; j < (1<<m_); j++) {
                f_[i][j] = INF;
            }
        }

        for (int i = 0; i < m_; i++) {
            int x = t_[i];
            f_[x][1<<i] = 0;
        }
        for (int S = 1; S < (1<<m_); S++) {
            for (int s = (S-1)&S; s; s = (s-1)&S) {
                for (int i = 0; i < n_; i++) {
                    f_[i][S] = min(f_[i][S], f_[i][s] + f_[i][S^s]);
                }
            }
            spfa(S);
        }
    }

private:
    void alloc() {
        f_ = new int*[n_]{};
        for (int i = 0; i < n_; i++) {
            f_[i] = new int[1<<m_]{};
        }
        in_ = new bool[n_]{};
    }

    void dealloc() {
        for (int i = 0; i < n_; i++) {
            delete[] f_[i];
        }
        delete[] f_;

        delete[] in_;
    }

    void spfa(int s) {
        for (int i = 0; i < n_; i++) {
            if (f_[i][s] < INF) {
                in_[i] = true;
                q_.push(i);
            }
        }
        while (!q_.empty()) {
            int u = q_.front();
            q_.pop();
            in_[u] = false;
            for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
                int v = g_.E[eidx].to;
                int w = g_.E[eidx].wt;
                if (f_[v][s] > f_[u][s] + w) {
                    f_[v][s] = f_[u][s] + w;
                    if (!in_[v]) {
                        in_[v] = true;
                        q_.push(v);
                    }
                }
            }
        }
    }

    const Graph &g_;
    const vector<int> &t_;
    int m_, n_;
public:
    int **f_;
    queue<int> q_;
    bool *in_;
};
