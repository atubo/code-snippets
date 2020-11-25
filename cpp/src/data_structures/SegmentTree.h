
// note it's 1-indexed
class SegmentTree {
  int N;
  int64_t *val, *lazy;

 public:
  SegmentTree(int N_): N(N_) {
    val = new int64_t[4*N+1]{};
    lazy = new int64_t[4*N+1]{};
  }

  ~SegmentTree() {
    delete[] val;
    delete[] lazy;
  }
  // add t to range [a, b]
  void update(int t, int a, int b) {
    update(1, t, 1, N, a, b);
  }

  // query range sum in [a, b]
  int64_t query(int a, int b) {
    return query(1, 1, N, a, b);
  }

 private:
  // add t to range [a, b], current node range is [l, r]
  void update(int k, int t, int l, int r, int a, int b) {
    if (a > b) return;
    pushDown(k, l, r);
    if (a <= l && r <= b) {
      val[k] += t * (r-l+1);
      lazy[k] += t;
      return;
    }
    if (l == r) return;
    int mid = (l + r) / 2;
    if (a <= mid) update(2*k,   t, l, mid, a, b);
    if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
    val[k] = val[2*k] + val[2*k+1];
  }

  void pushDown(int k, int l, int r) {
    if (!lazy[k] || l == r) return;
    lazy[2*k] += lazy[k];
    lazy[2*k+1] += lazy[k];
    int mid = (l + r) / 2;
    val[2*k] += (mid - l + 1) * lazy[k];
    val[2*k+1] += (r - mid) * lazy[k];
    lazy[k] = 0;
  }

  // query range sum in [a, b], current node is [l, r]
  int64_t query(int k, int l, int r, int a, int b) {
    if (!k) return 0;
    if (b < l || a > r) return 0;
    pushDown(k, l, r);
    if (a <= l && r <= b) return val[k];
    int64_t sum = 0;
    int mid = (l + r) / 2;
    if (a <= mid) sum += query(2*k, l, mid, a, b);
    if (mid < b)  sum += query(2*k+1, mid+1, r, a, b);
    return sum;
  }
};
