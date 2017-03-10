class SpfaDfs {
    static const int INF = INT_MAX;

public:
    struct Graph {
        static const int MAXN = 20010;
        vector<int> head;
        int N;

        int next[MAXN];
        int to[MAXN];
        int weight[MAXN];

        explicit Graph(int N_): N(N_) {
            head.resize(N);
        }

        void addEdge(int u, int v, int w) {
            static int q = 1;
            to[q] = v;
            weight[q] = w;
            next[q] = head[u];
            head[u] = q++;
        }
    };

    SpfaDfs(const Graph& g): graph(g) {
        N = graph.N;
    }

    bool check(int u) {
        init(u);
        return dfs(u);
    }

private:
    const Graph& graph;
    queue<int> Q;
    int N;
    vector<int> inq;    // if node is in queue
    vector<int> dist;
    vector<int> path;

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
        for (int j = graph.head[u]; j; j = graph.next[j]) {
            int v = graph.to[j];
            int w = graph.weight[j];
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
