
class TwoSat {
 public:
  TwoSat(int n): n_(n) {
    alloc();
  }

  ~TwoSat() {
    dealloc();
  }

  // xVal or yVal
  void addClause(int x, int xVal, int y, int yVal) {
    x = x * 2 + xVal;
    y = y * 2 + yVal;
    g_[x^1].push_back(y);
    g_[y^1].push_back(x);
  }

  bool dfs(int x) {
    if (mark_[x^1]) return false;
    if (mark_[x]) return true;
    stk_[sz_++] = x;
    mark_[x] = true;
    for (int v : g_[x]) {
      if (!dfs(v)) return false;
    }
    return true;
  }

  bool solve() {
    for (int i = 0; i < n_ * 2; i += 2) {
      if (!mark_[i] && !mark_[i^1]) {
        sz_ = 0;
        if (!dfs(i)) {
          while (sz_ > 0) mark_[stk_[--sz_]] = false;
          if (!dfs(i^1)) return false;
        }
      }
    }
    return true;
  }

  // note size is 2n
  const bool* getMark() const {
    return mark_;
  }

 private:
  void alloc() {
    stk_ = new int[2*n_]{};
    mark_ = new bool[2*n_]{};
    g_ = new vector<int>[2*n_]{};
  }

  void dealloc() {
    delete[] stk_;
    delete[] mark_;
    delete[] g_;
  }

  int n_;
  int sz_ = 0;
  int *stk_;
  bool *mark_;

  vector<int>* g_;
};
