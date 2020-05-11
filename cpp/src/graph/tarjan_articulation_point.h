
class TarjanArticulationPoint {
 public:
  // Note graph node is 0-indexed
  class Graph {
   public:
    struct Edge {
      int next, to;
    };

    vector<int> head;
    int eidx;
    int N, M;

    Edge *E;

    Graph(int N_, int M_):N(N_), M(M_) {
      head.resize(N);
      eidx = 0;

      for (int i = 0; i < N; i++) {
        head[i] = -1;
      }

      E = new Edge[M]{};
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

  // m is the number of undirected edges
  TarjanArticulationPoint(int n, int m): n_(n), g_(n, 2*m) {
    alloc();
  }

  ~TarjanArticulationPoint() {
    dealloc();
  }

  void addEdge(int u, int v) {
    g_.addEdge(u, v);
    g_.addEdge(v, u);
  }

  void solve() {
    dfs(0);
  }

  bool *art_; // whether a node is articulation point
 private:
  const int n_;
  Graph g_;

  int *dfn_;
  int *low_;
  bool *vis_;
  int tmpdfn_ = 0;
  int root_ = 0;

  void alloc() {
    dfn_ = new int[n_]{};
    low_ = new int[n_]{};
    vis_ = new bool[n_]{};
    art_ = new bool[n_]{};
  }

  void dealloc() {
    delete[] dfn_;
    delete[] low_;
    delete[] vis_;
    delete[] art_;
  }

  void dfs(int u) {
    dfn_[u] = low_[u] = tmpdfn_++;
    vis_[u] = true;
    int son = 0;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      if (!vis_[v]) {
        son++;
        dfs(v);
        low_[u] = min(low_[u], low_[v]);
        if (low_[v] >= dfn_[u]) {
          if (u != root_) art_[u] = true;
        }
      } else {
        low_[u] = min(low_[u], dfn_[v]);
      }
    }
    if (u == root_ && son > 1) art_[u] = true;
  }
};
