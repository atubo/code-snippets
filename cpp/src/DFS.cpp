#include <functional>
#include <stack>
#include <vector>

using namespace std;

// Note graph node is 0-indexed
class DFS {
public:
    static const int MAXN = 200;
    static const int MAXM = 10010;

    struct Edge {
        int next, to;
    } E[MAXM];

    int head[MAXN], dfn[MAXN], low[MAXN];
    bool vis[MAXN];
    int eidx;
    int tmpdfn;
    int N;

    DFS(int N_):N(N_) {
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
        memset(vis, 0, sizeof(vis));
        tmpdfn = 0;
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }

    void dfs(int u, int father) {
        vis[u] = true;
        dfn[u] = low[u] = tmpdfn++;
        for (int i = head[u]; i != -1; i = E[i].next) {
            int v = E[i].to;
            if (v != father && vis[v]) {
                low[u] = min(low[u], dfn[v]);
            }
            if (!vis[v]) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                // if low[v] > dfn[u], (u, v) is a bridge
                // if low[v] >= dfn[u], u is a cut vertex
            }
        }
    }
};
