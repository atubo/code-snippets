
class UnionFind {
 private:
  const int N;
  vector<int> rank;
  vector<int> parent;
  vector<int> size;

  void makeSet(int k) {
    assert(0 <= k && k < N);

    parent[k] = k;
    rank[k] = 0;
    size[k] = 1;
  }

  int link(int u, int v) {
    if (u == v) return u;
    if (rank[u] > rank[v]) {
      parent[v] = u;
      size[u] += size[v];
      return u;
    } else {
      parent[u] = v;
      size[v] += size[u];
      if (rank[u] == rank[v]) {
        rank[v]++;
      }
      return v;
    }
  }

 public:
  UnionFind(int n): N(n) {
    rank.resize(N);
    parent.resize(N);
    size.resize(N);

    reset();
  }

  void reset() {
    for (int i = 0; i < N; i++) {
      makeSet(i);
    }
  }

  int find(int k) {
    if (parent[k] == k) return k;
    int root = find(parent[k]);
    return parent[k] = root;
  }

  int join(int u, int v) {
    return link(find(u), find(v));
  }

  int count(int u) {
    return size[find(u)];
  }
};
