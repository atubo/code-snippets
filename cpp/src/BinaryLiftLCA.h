// Online algorithm, pre-computing O(N log N)
// Each query O(log N)

class BinaryLiftLCA {
public:
    int N, root;
    int MAXB;
    vector<vector<int> > adj;
    vector<int> depth;
    vector<vector<int> > father;

public:
    BinaryLiftLCA() {
        // initialization: N, root and adj
    }

    void preCompute() {
        MAXB = 0;
        int x = 1;
        while (x <= N) {
           MAXB++;
           x = x * 2;
        }

        depth.resize(N);
        father.resize(N);
        for (int i = 0; i < N; i++) {
            father[i].resize(MAXB, -1);
        }

        vector<bool> visited(N, false);
        dfs(root, -1, visited, 0);

        binaryLift();
    }

    void dfs(int x, int f, vector<bool>& visited, int d) {
        depth[x] = d;
        father[x][0] = f;
        visited[x] = true;
        for (int i = 0; i < (int)adj[x].size(); i++) {
            int u = adj[x][i];
            if (!visited[u]) dfs(u, x, visited, d+1);
        }
    }

    void binaryLift() {
        for (int j = 1; j < MAXB; j++) {
            for (int i = 0; i < N; i++) {
                if (father[i][j-1] != -1) {
                    father[i][j] = father[father[i][j-1]][j-1];
                }
            }
        }
    }

    int findLCA(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        for (int b = MAXB-1; b >= 0; b--) {
            if (father[u][b] == -1) continue;
            if (depth[father[u][b]] >= depth[v]) {
                u = father[u][b];
            }
        }

        if (u == v) return u;

        for (int b = MAXB-1; b >= 0; b--) {
            if (father[u][b] == -1) continue;
            if (father[u][b] != father[v][b]) {
                u = father[u][b];
                v = father[v][b];
            }
        }
        return father[u][0];
    }
};
