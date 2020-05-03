
class BaseTree {
  // Note graph node is 0-indexed
  class Graph {
   public:
    struct Edge {
      int next, to, wt;
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
    void addEdge(int u, int v, int w) {
      E[eidx].to = v;
      E[eidx].next = head[u];
      E[eidx].wt = w;
      head[u] = eidx++;
    }
  };

  class Ring {
   public:
    Ring(int n): n_(n) {
      alloc();
    }

    ~Ring() {
      dealloc();
    }

    int* w;   // distance to the next node
    int64_t* d;   // depth of its tree
    const int n_;
   private:

    void alloc() {
      w = new int[n_]{};
      d = new int64_t[n_]{};
    }

    void dealloc() {
      delete[] w;
      delete[] d;
    }
  };

 public:
  BaseTree(int n): n_(n), g_(n, 2*n) {
    alloc();
  }

  ~BaseTree() {
    dealloc();
  }

  void addEdge(int u, int v, int w) {
    g_.addEdge(u, v, w);
    g_.addEdge(v, u, w);
  }

  void build() {
    dfs1(0, -1);
    for (int x : rng_) {
      dfs2(x, -1);
    }
    ring_ = std::make_shared<Ring>(rng_.size());
    for (int i = 0; i < (int)rng_.size(); i++) {
      int u = rng_[i];
      int v = rng_[(i+1)%rng_.size()];
      ring_->d[i] = maxd_[u];
      for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
        if (g_.E[eidx].to == v) {
          ring_->w[i] = g_.E[eidx].wt;
          break;
        }
      }
    }
  }

  vector<int> rng_; // all nodes on the ring
  std::shared_ptr<Ring> ring_;
 private:
  int n_;
  Graph g_;

  int* fa_;
  bool* vis_;
  int* nb_[2];
  int64_t* maxd_;
  int* fw_;   // weight of the father edge

  void alloc() {
    fa_ = new int[n_]{};
    vis_ = new bool[n_]{};
    nb_[0] = new int[n_]{};
    nb_[1] = new int[n_]{};
    memset(nb_[0], -1, n_*sizeof(int));
    memset(nb_[1], -1, n_*sizeof(int));
    maxd_ = new int64_t[n_]{};
    fw_ = new int[n_]{};
  }

  void dealloc() {
    delete[] fa_;
    delete[] vis_;
    delete[] nb_[0];
    delete[] nb_[1];
    delete[] maxd_;
    delete[] fw_;
  }

  // to find the loop
  bool dfs1(int u, int f) {
    fa_[u] = f;
    vis_[u] = true;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      if (v != f) {
        if (vis_[v]) {
          traverse(u, v);
          return true;
        }
        if (dfs1(v, u)) return true;
      }
    }
    return false;
  }

  // traverse the loop, start point u, end point v
  void traverse(int u, int v) {
    int x = u, last = v;
    while (x != v) {
      nb_[0][x] = fa_[x];
      nb_[1][x] = last;
      rng_.push_back(x);
      last = x;
      x = fa_[x];
    }
    nb_[0][x] = u;
    nb_[1][x] = last;
    rng_.push_back(x);
  }

  // start from each node in the root, collect stat of subtree
  void dfs2(int u, int f) {
    maxd_[u] = 0;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      int w = g_.E[eidx].wt;
      if (v != nb_[0][u] && v != nb_[1][u] && v != f) {
        fw_[v] = w;
        dfs2(v, u);
        maxd_[u] = max(maxd_[u], maxd_[v] + w);
      }
    }
  }
};
