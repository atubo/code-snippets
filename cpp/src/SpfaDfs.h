// Determine if there is any negative weight loop
// Nodes in graph are 0-indexed
// Node N is a virtual node that has 0 weight edge to all nodes
// But we don't have to explicitly add that node
class SpfaDfs {
public:
    struct Edge {
        int next, to;
        int wt;
    };

    SpfaDfs(int N_, int M): N(N_) {
        inq = new bool[N]{};
        dist = new int[N];
        head = new int[N];
        eTotal = 0;
        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
        E = new Edge[M]{};
    }

    ~SpfaDfs() {
        delete[] inq;
        delete[] dist;
        delete[] head;
        delete[] E;
    }

    void addEdge(int u, int v, int w) {
        E[eTotal].to = v;
        E[eTotal].next = head[u];
        E[eTotal].wt = w;
        head[u] = eTotal++;
    }

    bool check() {
        init();
        for (int i = 0; i < N; i++) {
            if (!dfs(i)) return false;
        }
        return true;
    }

private:
    int N;
    bool *inq;  // if node is in queue
    int *dist;

    int *head;
    int eTotal;
    Edge *E;

    void init() {
        memset(inq, 0, N*sizeof(bool));
        memset(dist, 0, N*sizeof(int));
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
