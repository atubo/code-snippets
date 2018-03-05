// Stoer-Wagner undirected graph global min-cut algorithm
// for dense graphs, time complexity O(N^3)

class StoerWagnerMinCutDense {
private:
    int N;
    int *wt;
    bool *vis;
    bool *merged;
    int **adj;

public:
    StoerWagnerMinCutDense(int N_): N(N_) {
        wt  = new int[N]{};
        vis = new bool[N]{};
        merged = new bool[N]{};
        adj = new int*[N];
        for (int i = 0; i < N; i++) {
            adj[i] = new int[N]{};
        }
    }

    ~StoerWagnerMinCutDense() {
        delete[] wt;
        delete[] vis;
        delete[] merged;
        for (int i = 0; i < N; i++) {
            delete[] adj[i];
        }
        delete[] adj;
    }

    void addEdge(int u, int v, int w) {
        adj[u][v] = adj[v][u] = w;
    }

    int minimumCut() {
        int ans = INT_MAX;
        for (int i = 0; i < N-1; i++) {
            int s, t;
            int mincut = minimumCutPhase(s, t);
            ans = min(ans, mincut);
            if (ans == 0) return 0;
            merged[t] = 1;
            for (int j = 0; j < N; j++) {
                if (!merged[j]) {
                    adj[s][j] += adj[t][j];
                    adj[j][s] += adj[j][t];
                }
            }
        }
        return ans;
    }

private:
    int minimumCutPhase(int &s, int &t) {
        memset(wt,  0, N * sizeof(int));
        memset(vis, 0, N * sizeof(bool));
        int mincut = 0;
        s = -1;
        t = -1;
        for (int i = 0; i < N; i++) {
            int maxw = -1;
            int u = -1;
            for (int j = 0; j < N; j++) {
                if (!merged[j] && !vis[j] && wt[j] > maxw) {
                    u = j;
                    maxw = wt[j];
                }
            }
            if (u == -1) return mincut;
            s = t; t = u;
            mincut = maxw;
            vis[u] = 1;
            for (int j = 0; j < N; j++) {
                if (!merged[j] && !vis[j]) {
                    wt[j] += adj[u][j];
                }
            }
        }
        return mincut;
    }
};
