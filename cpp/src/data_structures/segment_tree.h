
// note it's 1-indexed
class SegmentTree {
  int n_;
  int64_t *val_, *lazy_;

 public:
  SegmentTree(int n): n_(n) {
    val_ = new int64_t[4*n_+1]{};
    lazy_ = new int64_t[4*n_+1]{};
  }

  ~SegmentTree() {
    delete[] val_;
    delete[] lazy_;
  }
  // add t to range [a, b]
  void update(int t, int a, int b) {
    if (a > b) return;
    update(1, t, 1, n_, a, b);
  }

  // query range sum in [a, b]
  int64_t query(int a, int b) {
    assert(1 <= a && a <= b && b <= n_);
    return query(1, 1, n_, a, b);
  }

 private:
  // add t to range [a, b], current node range is [l, r]
  void update(int k, int t, int l, int r, int a, int b) {
    pushDown(k, l, r);
    if (a <= l && r <= b) {
      val_[k] += t * (r-l+1);
      lazy_[k] += t;
      return;
    }
    int mid = (l + r) / 2;
    if (a <= mid) update(2*k,   t, l, mid, a, b);
    if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
    val_[k] = val_[2*k] + val_[2*k+1];
  }

  void pushDown(int k, int l, int r) {
    if (!lazy_[k] || l == r) return;
    lazy_[2*k] += lazy_[k];
    lazy_[2*k+1] += lazy_[k];
    int mid = (l + r) / 2;
    val_[2*k] += (mid - l + 1) * lazy_[k];
    val_[2*k+1] += (r - mid) * lazy_[k];
    lazy_[k] = 0;
  }

  // query range sum in [a, b], current node is [l, r]
  int64_t query(int k, int l, int r, int a, int b) {
    pushDown(k, l, r);
    if (a <= l && r <= b) return val_[k];
    int64_t sum = 0;
    int mid = (l + r) / 2;
    if (a <= mid) sum += query(2*k, l, mid, a, b);
    if (mid < b)  sum += query(2*k+1, mid+1, r, a, b);
    return sum;
  }
};
