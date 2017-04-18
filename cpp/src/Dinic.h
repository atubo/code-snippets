
namespace Dinic {
const int inf = 0x3f3f3f3f;
const int MAXN = 1000;
const int MAXM = 5 * MAXN * MAXN;
int head[MAXN];
struct Edge {
    int to, next, cap;
} E[MAXM];
int e;

void init() {
    memset(head, -1, sizeof(head));
}

void addEdge(int x, int y, int z) {
    E[e] = {y, head[x], z};
    head[x] = e++;
    E[e] = {x, head[y], 0};
    head[y] = e++;
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
        for (int i = head[u]; i != -1; i = E[i].next) {
            int v = E[i].to;
            if (d[v] == -1 && E[i^1].cap) {
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
    for (int i = head[x]; i != -1; i = E[i].next) {
        int v = E[i].to;
        if (d[v] == d[x] - 1) {
            int k = dfs(v, min(low-ret, E[i].cap), t);
            if (k > 0) {
                E[i].cap -= k;
                E[i^1].cap += k;
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
