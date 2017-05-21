
class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
private:
    static const int MAXN = 100;
    static const int MAXM = 1000;
    int head[MAXN], curr[MAXN];
    struct Edge {
        int to, next, cap;
    } E[MAXM];
    int e;

public:
    Dinic() {
        reset();
    }

    void reset() {
        e = 0;
        memset(head, -1, sizeof(head));
    }

    void addEdge(int x, int y, int w, int rw = 0) {
        E[e] = {y, head[x], w};
        head[x] = e++;
        E[e] = {x, head[y], rw};
        head[y] = e++;
    }

private:
    int d[MAXN];

    bool bfs(int s, int t) {
        memset(d, -1, sizeof(d));
        queue<int> q;
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
                    if (v == s) return true;
                }
            }
        }
        return false;
    }

    int dfs(int x, int low, int t) {
        if (x == t || !low) return low;
        int ret = 0;
        for (int &i = curr[x]; i != -1; i = E[i].next) {
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

public:
    int dinic(int s, int t) {
        int ans = 0;
        while (bfs(s, t)) {
            for (int i = 0; i < MAXN; i++) {
                curr[i] = head[i];
            }
            int k = dfs(s, inf, t);
            if (k > 0) ans += k;
        }
        return ans;
    }
};
