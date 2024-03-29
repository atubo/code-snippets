// Hungarian method to find maximal match in bipartite graph
// using DFS, time complexity O(N^3)
class Hungarian {
 private:
  int nx_, ny_;
  bool** g_;

  int *cx_, *cy_;
  bool *mk_;

  void alloc() {
    g_ = new bool*[nx_];
    for (int i = 0; i < nx_; i++) {
      g_[i] = new bool[ny_];
    }
    cx_ = new int[nx_];
    cy_ = new int[ny_];
    mk_ = new bool[ny_];
  }

  void dealloc() {
    for (int i = 0; i < nx_; i++) {
      delete[] g_[i];
    }
    delete[] g_;

    delete[] cx_;
    delete[] cy_;
    delete[] mk_;
  }

  int path(int u) {
    for (int v = 0; v < ny_; v++) {
      if (g_[u][v] && !mk_[v]) {
        mk_[v] = true;
        if (cy_[v] == -1 || path(cy_[v])) {
          cx_[u] = v;
          cy_[v] = u;
          return 1;
        }
      }
    }
    return 0;
  }

 public:
  Hungarian(int nx, int ny): nx_(nx), ny_(ny) {
    alloc();
    reset();
  }

  ~Hungarian() {
    dealloc();
  }

  void reset() {
    for (int i = 0; i < nx_; i++) {
      memset(g_[i], 0, ny_ * sizeof(bool));
    }
  }

  void addEdge(int x, int y) {
    g_[x][y] = true;
  }

  int maxMatch() {
    int res = 0;
    memset(cx_, -1, nx_ * sizeof(int));
    memset(cy_, -1, ny_ * sizeof(int));
    for (int i = 0; i < nx_; i++) {
      if (cx_[i] == -1) {
        memset(mk_, 0, ny_ * sizeof(bool));
        res += path(i);
      }
    }
    return res;
  }

  struct Match {
    int nx, ny;
    const int *cx, *cy;
    bool const * const *g;
  };

  Match getMatch() const {
    return {nx_, ny_, cx_, cy_, g_};
  }
};
