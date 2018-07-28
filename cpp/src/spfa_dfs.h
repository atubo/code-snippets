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

    SpfaDfs(int n, int m): n_(n) {
        inq_ = new bool[n_]{};
        dist_ = new int64_t[n_];
        vis_ = new bool[n_]{};
        head_ = new int[n_];
        e_total_ = 0;
        for (int i = 0; i < n_; i++) {
            head_[i] = -1;
        }
        e_ = new Edge[m]{};
    }

    ~SpfaDfs() {
        delete[] inq_;
        delete[] dist_;
        delete[] vis_;
        delete[] head_;
        delete[] e_;
    }

    void addEdge(int u, int v, int64_t w) {
        e_[e_total_].to = v;
        e_[e_total_].next = head_[u];
        e_[e_total_].wt = w;
        head_[u] = e_total_++;
    }

    bool check(bool include_zero = false) {
        init();
        for (int i = 0; i < n_; i++) {
            if (include_zero) memset(vis_, 0, n_*sizeof(bool));
            if (!dfs(i, include_zero)) return false;
        }
        return true;
    }

private:
    int n_;
    bool *inq_;  // if node is in queue
    int64_t *dist_;
    bool *vis_;

    int *head_;
    int e_total_;
    Edge *e_;

    void init() {
        memset(inq_, 0, n_*sizeof(bool));
        memset(dist_, 0, n_*sizeof(int64_t));
    }

    bool dfs(int u, bool include_zero) {
        if (inq_[u]) return false;
        inq_[u] = 1;
        vis_[u] = true;
        for (int eidx = head_[u]; eidx != -1; eidx = e_[eidx].next) {
            int v = e_[eidx].to;
            int64_t w = e_[eidx].wt;
            if (include_zero && dist_[v] == dist_[u] + w && inq_[v]) return false;
            if (dist_[v] > dist_[u] + w ||
                (include_zero && dist_[v] == dist_[u] + w && !vis_[v])) {
                dist_[v] = dist_[u] + w;
                if (!dfs(v, include_zero)) return false;
            }
        }
        inq_[u] = 0;
        return true;
    }
};
