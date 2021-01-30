class FenwickTree {
 public:
  // 1-indexed
  FenwickTree(int size): n_(size) {
    tree_ = new int64_t[n_+1]{};
  }

  ~FenwickTree() {
    delete[] tree_;
  }

  void clear() {
    memset(tree_, 0, (n_+1) * sizeof(int64_t));
  }

  // add v to value at x
  void add(int x, int v) {
    while(x <= n_) {
      tree_[x] += v;
      x += (x & -x);
    }
  }

  // get cumulative sum up to and including x
  int64_t query(int x) const {
    int64_t res = 0;
    while(x) {
      res += tree_[x];
      x -= (x & -x);
    }
    return res;
  }

  // get result for [x, y]
  int64_t query(int x, int y) const {
    return query(y) - (x > 1 ? query(x-1) : 0);
  }

  // index of first element with cumulative sum >= x
  int lowerBound(int64_t x) {
    int clz = __builtin_clz(n_);
    int idx = 0, mask = 1 << (31 - clz);     // first power of 2 <= n_
    while (mask) {
      int t = idx + mask;
      if (t <= n_ && x > tree_[t]) {
        idx = t;
        x -= tree_[t];
      }
      mask >>= 1;
    }
    return idx+1;
  }

  int upperBound(int64_t x) {
    int p = lowerBound(x);
    if (p <= n_ && query(p) == x) p = lowerBound(x+1);
    return p;
  }

 private:
  int64_t* tree_;
  const int n_;
};
