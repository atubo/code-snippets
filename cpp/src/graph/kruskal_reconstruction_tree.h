
// Node is 0-indexed
class KruskalReconstructionTree {
 public:
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

  struct Edge {
    int u, v, w;
    bool operator < (const Edge& other) const {
      return w < other.w;
    }
  };

 private:
  int n_;
  Graph g_;
  int* fa_; // for union-find
  int* val_; // weight of internal nodes
  vector<Edge> e_;

  void alloc() {
    const int lim = 2*n_;
    fa_ = new int[lim]{};
    val_ = new int[lim]{};
    for (int i = 0; i < lim; i++) {
      fa_[i] = i;
    }
  }

  void dealloc() {
    delete[] fa_;
    delete[] val_;
  }

  void addTreeEdge(int u, int v) {
    g_.addEdge(u, v);
  }

  int find(int x) {
    return fa_[x] == x ? x : fa_[x] = find(fa_[x]);
  }

 public:
  KruskalReconstructionTree(int n): n_(n), g_(2*n-1, 2*n-2) {
    alloc();
  }

  ~KruskalReconstructionTree() {
    dealloc();
  }

  void kruskal() {
    sort(e_.begin(), e_.end());
    for (int idx=n_-1, i=0; i < (int)e_.size(); i++) {
      int fu = find(e_[i].u), fv = find(e_[i].v);
      if (fu == fv) continue;
      fa_[fu] = fa_[fv] = ++idx;
      val_[idx] = e_[i].w;
      addTreeEdge(idx, fu);
      addTreeEdge(idx, fv);
      if (idx == 2*n_-2) break;
    }
  }

  void addEdge(int u, int v, int w) {
    e_.push_back({u, v, w});
  }

  const Graph& getTree() const {
    return g_;
  }
};
