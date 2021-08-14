
// Find biconnected components in a undirected graph
class TarjanIndirectedBcc {
 public:
  // Note graph node is 0-indexed
  class Graph {
   public:
    struct Edge {
      int next, from, to;
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

    void addEdge(int u, int v) {
      E[eidx].from = u;
      E[eidx].to = v;
      E[eidx].next = head[u];
      head[u] = eidx++;
    }
  };

  // m is the number of undirected edges
  TarjanIndirectedBcc(int n, int m): n_(n), g_(n, 2*m) {
    alloc();
  }

  ~TarjanIndirectedBcc() {
    dealloc();
  }

  void addEdge(int u, int v) {
    g_.addEdge(u, v);
    g_.addEdge(v, u);
  }

  void solve() {
    for (int i = 0; i < n_; i++) {
      if (!vis_[i]) {
        list<Graph::Edge> st;
        dfs(i, st, true);
      }
    }
  }

  bool *art_; // whether a node is articulation point
  int *belong_;   // node id => bcc id
  vector<set<int>> art_belong_; // for AP, node is => list of bcc ids
 private:
  const int n_;
  Graph g_;

  int *dfn_;
  int *low_;
  bool *vis_;
  int *parent_;
  int tmpdfn_ = 0;
  int bcc_id_ = 0;

  void alloc() {
    dfn_ = new int[n_]{};
    low_ = new int[n_]{};
    vis_ = new bool[n_]{};
    art_ = new bool[n_]{};
    parent_ = new int[n_]{};
    belong_ = new int[n_]{};
    art_belong_.resize(n_);
  }

  void dealloc() {
    delete[] dfn_;
    delete[] low_;
    delete[] vis_;
    delete[] art_;
    delete[] parent_;
    delete[] belong_;
  }

  void dfs(int u, list<Graph::Edge> &st, bool root = false) {
    dfn_[u] = low_[u] = tmpdfn_++;
    vis_[u] = true;
    int son = 0;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      if (!vis_[v]) {
        son++;
        parent_[v] = u;
        st.push_back({-1, u, v});
        dfs(v, st);
        low_[u] = min(low_[u], low_[v]);
        if (low_[v] >= dfn_[u]) {
          if (!root) {
            art_[u] = true;
            art_belong_[u].insert(bcc_id_);
            while (st.back().from != u || st.back().to != v) {
              int p = st.back().from;
              int q = st.back().to;
              belong_[p] = bcc_id_;
              belong_[q] = bcc_id_;
              if (art_[p]) {
                art_belong_[p].insert(bcc_id_);
              }
              if (art_[q]) {
                art_belong_[q].insert(bcc_id_);
              }
              st.pop_back();
            }
            belong_[st.back().from] = bcc_id_;
            belong_[st.back().to] = bcc_id_;
            bcc_id_++;
            st.pop_back();
          }
        }
      } else if (v != parent_[u]) {
        low_[u] = min(low_[u], dfn_[v]);
        if (dfn_[v] < dfn_[u]) {
          st.push_back({-1, u, v});
        }
      }
    }
    if (root) {
      if (son > 1) {
        art_[u] = true;
        art_belong_[u].insert(bcc_id_);
      }
      while (!st.empty()) {
        int p = st.back().from;
        int q = st.back().to;
        belong_[p] = bcc_id_;
        belong_[q] = bcc_id_;
        if (art_[p]) {
          art_belong_[p].insert(bcc_id_);
        }
        if (art_[q]) {
          art_belong_[q].insert(bcc_id_);
        }
        st.pop_back();
      }
      bcc_id_++;
    }
  }
};
