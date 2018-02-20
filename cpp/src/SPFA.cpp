class SPFA {
    const static int MAXM = 620000;
    const static int64_t INF;

    struct Edge {
        int next, to, wt;
    };

public:
    SPFA(int N_): N(N_) {
        head = new int[N];
        eTotal = 0;
        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
        E = new Edge[MAXM]{};

        inq = new int[N];
        cnt = new int[N];
    }

    ~SPFA() {
        delete[] head;
        delete[] E;
        delete[] inq;
        delete[] cnt;
    }

    void addEdge(int u, int v, int w) {
        E[eTotal].to = v;
        E[eTotal].next = head[u];
        E[eTotal].wt = w;
        head[u] = eTotal++;
    }

    void init(int src) {
        while (!Q.empty()) Q.pop();
        dist.clear();
        path.clear();

        memset(inq, 0, N * sizeof(int));
        memset(cnt, 0, N * sizeof(int));
        dist.resize(N, INF);
        path.resize(N, src);

        dist[src] = 0;
    }

    bool solve(int src) {
        init(src);

        Q.push(src);
        inq[src]++;
        cnt[src]++;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            inq[u]--;

            for (int eidx = head[u]; eidx != -1; eidx = E[eidx].next) {
                int v = E[eidx].to;
                int64_t w = E[eidx].wt;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    path[v] = u;
                    if (!inq[v]) {
                        Q.push(v);
                        inq[v]++;
                        cnt[v]++;
                        if (cnt[v] > N) return false;
                    }
                }
            }
        }
        return true;
    }

    const vector<int64_t>& getDist() const {return dist;}

    const vector<int>& getPath() const {return path;}

private:
    int *head;
    int eTotal;
    Edge *E;

    queue<int> Q;
    int N;
    int *inq;    // if node is in queue
    int *cnt;    // how many time a node has been in the queue
    vector<int64_t> dist;
    vector<int> path;
};

const int64_t SPFA::INF = LLONG_MAX/4;
