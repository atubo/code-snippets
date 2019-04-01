
class SteinerTreeFloyd {
public:
    SteinerTreeFloyd(int n, const vector<int> &t):
        n_(n), r_(t.size()), ALL((1<<r_)-1), t_(t) {
        alloc();
    }

    ~SteinerTreeFloyd() {
        dealloc();
    }

    void addEdge(int u, int v, int w) {
        g_[u][v] = g_[v][u] = min(g_[v][u], w);
    }

    void solve() {
        for (int k = 0; k < n_; k++) {
            for (int i = 0; i < n_; i++) {
                for (int j = 0; j < n_; j++) {
                    g_[i][j] = min(g_[i][j], g_[i][k] + g_[k][j]);
                }
            }
        }
        for (int i = 0; i < r_; i++) {
            for (int j = 0; j < n_; j++) {
                dp[1<<i][j] = g_[t_[i]][j];
            }
        }

        for (int i = 1; i <= ALL; i++) {
            if (!(i&(i-1))) continue;
            for (int j = 0; j < n_; j++) dp[i][j] = INF;
            for (int j = 0; j < n_; j++) {
                int tmp = INF;
                for (int s = i&(i-1); s; s=i&(s-1)) {
                    tmp = min(tmp, dp[s][j]+dp[i^s][j]);
                }
                for (int k = 0; k < n_; k++) {
                    dp[i][k] = min(dp[i][k], g_[j][k]+tmp);
                }
            }
        }
    }

    int **dp;

private:
    int n_;
    int r_;
    const int ALL;
    const vector<int> &t_;
    int **g_;

    const int INF = 0x3F3F3F3F;

    void alloc() {
        dp = new int*[1<<r_]{};
        for (int i = 0; i <= ALL; i++) {
            dp[i] = new int[n_]{};
        }

        g_ = new int*[n_]{};
        for (int i = 0; i < n_; i++) {
            g_[i] = new int[n_]{};
            for (int j = 0; j < n_; j++) g_[i][j] = INF;
            g_[i][i] = 0;
        }
    }

    void dealloc() {
        for (int i = 0; i <= ALL; i++) {
            delete dp[i];
        }
        delete[] dp;

        for (int i = 0; i < n_; i++) {
            delete g_[i];
        }
        delete g_;
    }
};
