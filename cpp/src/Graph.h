// Note graph node is 0-indexed
class Graph {
    static const int MAXM = 1000;
public:
    struct Edge {
        int next, to;
    };

    vector<int> head;
    int eidx;
    int N;

    Edge *E;

    Graph(int N_):N(N_) {
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }

        E = new Edge[MAXM]{};
    }

    ~Graph() {
        delete[] E;
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};
