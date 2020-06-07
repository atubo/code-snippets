// Online algorithm, pre-computing O(N log N)
// Each query O(log N)

class BinaryLiftLCA {
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

  int N_, root_;
  int MAXB_;
  Graph g_;
 public:
  int* depth;
  int** father;

 public:
  BinaryLiftLCA(int N, int root)
      : N_(N), root_(root), MAXB_(log2(N)+1), g_(N, 2*(N-1)) {
        alloc();
      }

  ~BinaryLiftLCA() {
    dealloc();
  }

  void addEdge(int u, int v) {
    g_.addEdge(u, v);
    g_.addEdge(v, u);
  }

  void build() {
    dfs(root_, -1, 0);

    binaryLift();
  }

  int findLCA(int u, int v) const {
    if (depth[u] < depth[v]) swap(u, v);
    for (int b = MAXB_-1; b >= 0; b--) {
      if (father[u][b] == -1) continue;
      if (depth[father[u][b]] >= depth[v]) {
        u = father[u][b];
      }
    }

    if (u == v) return u;

    for (int b = MAXB_-1; b >= 0; b--) {
      if (father[u][b] == -1) continue;
      if (father[u][b] != father[v][b]) {
        u = father[u][b];
        v = father[v][b];
      }
    }
    return father[u][0];
  }

 private:
  void alloc() {
    depth = new int[N_]{};
    father = new int*[N_]{};
    for (int i = 0; i < N_; i++) {
      father[i] = new int[MAXB_]{};
      memset(father[i], -1, MAXB_*sizeof(int));
    }
  }

  void dealloc() {
    delete[] depth;
    for (int i = 0; i < N_; i++) {
      delete[] father[i];
    }
    delete[] father;
  }

  void dfs(int x, int f, int d) {
    depth[x] = d;
    father[x][0] = f;
    for (int eidx = g_.head[x]; ~eidx; eidx = g_.E[eidx].next) {
      int u = g_.E[eidx].to;
      if (u != f) dfs(u, x, d+1);
    }
  }

  void binaryLift() {
    for (int j = 1; j < MAXB_; j++) {
      for (int i = 0; i < N_; i++) {
        if (father[i][j-1] != -1) {
          father[i][j] = father[father[i][j-1]][j-1];
        }
      }
    }
  }
};
