// Determine if there is any negative weight loop
// Nodes in graph are 0-indexed
// Node N is a virtual node that has 0 weight edge to all nodes
// But we don't have to explicitly add that node
class SpfaDfs {
public:
    struct Edge {
        int next, to;
        int64_t wt;
    };

    SpfaDfs(int N_, int M_): N(N_) {
        inq = new bool[N]{};
        dist = new int64_t[N];
        vis_ = new bool[N]{};
        head = new int[N];
        eTotal = 0;
        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
        E = new Edge[M_]{};
    }

    ~SpfaDfs() {
        delete[] inq;
        delete[] dist;
        delete[] vis_;
        delete[] head;
        delete[] E;
    }

    void addEdge(int u, int v, int64_t w) {
        E[eTotal].to = v;
        E[eTotal].next = head[u];
        E[eTotal].wt = w;
        head[u] = eTotal++;
    }

    bool check(bool include_zero = false) {
        init();
        for (int i = 0; i < N; i++) {
            if (include_zero) memset(vis_, 0, N*sizeof(bool));
            if (!dfs(i, include_zero)) return false;
        }
        return true;
    }

private:
    int N;
    bool *inq;  // if node is in queue
    int64_t *dist;
    bool *vis_;

    int *head;
public:
    int eTotal;
    Edge *E;

    void init() {
        memset(inq, 0, N*sizeof(bool));
        memset(dist, 0, N*sizeof(int64_t));
    }

    bool dfs(int u, bool include_zero) {
        if (inq[u]) return false;
        inq[u] = 1;
        vis_[u] = true;
        for (int eidx = head[u]; eidx != -1; eidx = E[eidx].next) {
            int v = E[eidx].to;
            int64_t w = E[eidx].wt;
            if (include_zero && dist[v] == dist[u] + w && inq[v]) return false;
            if (dist[v] > dist[u] + w ||
                (include_zero && dist[v] == dist[u] + w && !vis_[v])) {
                dist[v] = dist[u] + w;
                if (!dfs(v, include_zero)) return false;
            }
        }
        inq[u] = 0;
        return true;
    }
};
