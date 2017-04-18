
namespace Dinic {
const int inf = 0x3f3f3f3f;
const int MAXN = 1000;
const int MAXM = 5 * MAXN * MAXN;
int be[MAXN];
int e, ne[MAXM], to[MAXM], c[MAXM];

void init() {
    memset(be, -1, sizeof(be));
}

void addEdge(int x, int y, int z) {
    to[e] = y, ne[e] = be[x], be[x] = e;
    c[e] = z, e++;
    to[e] = x, ne[e] = be[y], be[y] = e;
    c[e] = 0, e++;
}

int d[MAXN];


bool bfs(int s, int t) {
    queue<int> q;
    memset(d, -1, sizeof(d));
    q.push(t);
    d[t] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = be[u]; i != -1; i = ne[i]) {
            int v = to[i];
            if (d[v] == -1 && c[i^1]) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    return d[s] != -1;
}

int dfs(int x, int low, int t) {
    if (x == t || !low) return low;
    int ret = 0;
    for (int i = be[x]; i != -1; i = ne[i]) {
        int v = to[i];
        if (d[v] == d[x] - 1) {
            int k = dfs(v, min(low-ret, c[i]), t);
            if (k > 0) {
                c[i] -= k;
                c[i^1] += k;
                ret += k;
            }
        }
    }
    return ret;
}

int dinic(int s, int t) {
    int ans = 0;
    while (bfs(s, t)) {
        int k = dfs(s, inf, t);
        if (k > 0) ans += k;
    }
    return ans;
}
}
