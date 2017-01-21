
class VirtualTree {
public:
    int N, root;
    int MAXB;
    vector<vector<int> > adj;
    vector<int> dfn;
    vector<int> depth;
    vector<vector<int> > father;
    int sz;

    vector<int> stk;
    vector<pair<int, int> > vEdges;

public:
    VirtualTree() {
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
        dfn.resize(N);
        for (int i = 0; i < N; i++) {
            father[i].resize(MAXB, -1);
        }

        vector<bool> visited(N, false);
        sz = 0;
        dfs(root, -1, visited, 0);

        binaryLift();

        stk.resize(N);
    }

    void dfs(int x, int f, vector<bool>& visited, int d) {
        dfn[x] = sz++;
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

    struct CmpByDfn {
        CmpByDfn(const VirtualTree& t): m_t(t) {}
        const VirtualTree& m_t;

        bool operator()(int i, int j) {
            return m_t.dfn[i] < m_t.dfn[j];
        }
    };

    int buildVirtualTree(vector<int>& vertices, int k) {
        vEdges.clear();

        sz = 0;
        int cnt = k;
        sort(vertices.begin(), vertices.begin()+k, CmpByDfn(*this));

        for (int i = 0; i < k; i++) {
            int u = vertices[i];
            int lca = (sz > 0 ? findLCA(u, stk[sz-1]) : u);
            if (sz == 0 || lca == stk[sz-1]) stk[sz++] = u;
            else {
                while (sz - 2 >= 0 && depth[stk[sz-2]] >= depth[lca]) {
                    addVirtualEdge(stk[sz-2], stk[sz-1]);
                    sz--;
                }

                if (stk[sz-1] != lca) {
                    addVirtualEdge(lca, stk[--sz]);
                    stk[sz++] = lca;
                    vertices[cnt++] = lca;
                }

                stk[sz++] = u;
            }
        }

        for (int i = 0; i < sz-1; i++) {
            addVirtualEdge(stk[i], stk[i+1]);
        }

        sort(vEdges.begin(), vEdges.end());
        return cnt;
    }

    void addVirtualEdge(int u, int v) {
        vEdges.push_back(make_pair(u, v));
    }
};
