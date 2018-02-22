class SpfaDfs {
    static const int MAXM = 610000;
    static const int INF = INT_MAX;

public:
    struct Edge {
        int next, to, wt;
    };

    SpfaDfs(int N_): N(N_) {
        head = new int[N];
        eTotal = 0;
        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
        E = new Edge[MAXM]{};
    }

    ~SpfaDfs() {
        delete[] head;
        delete[] E;
    }

    void addEdge(int u, int v, int w) {
        E[eTotal].to = v;
        E[eTotal].next = head[u];
        E[eTotal].wt = w;
        head[u] = eTotal++;
    }

    bool check(int u) {
        init(u);
        return dfs(u);
    }

    int getDist(int u) const {return dist[u];}

private:
    queue<int> Q;
    int N;
    vector<int> inq;    // if node is in queue
    vector<int> dist;
    vector<int> path;

    int *head;
    int eTotal;
    Edge *E;

    void init(int src) {
        while (!Q.empty()) Q.pop();
        inq.clear();
        dist.clear();
        path.clear();

        inq.resize(N, 0);
        dist.resize(N, INF);
        path.resize(N, src);

        dist[src] = 0;
    }

    bool dfs(int u) {
        if (inq[u]) return false;
        inq[u] = 1;
        for (int eidx = head[u]; eidx != -1; eidx = E[eidx].next) {
            int v = E[eidx].to;
            int w = E[eidx].wt;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!dfs(v)) return false;
            }
        }
        inq[u] = 0;
        return true;
    }
};

const int SpfaDfs::INF;
