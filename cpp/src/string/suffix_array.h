/*
Suffix array O(n lg^2 n)
LCP table O(n)
*/
// see http://web.stanford.edu/class/cs97si/suffix-array.pdf

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)

// lcp(i) = LCP(i, i+1)
class SuffixArray {
 public:
  SuffixArray(const char* s) : n_(strlen(s)), s_(s) {
    assert(n_ > 0);
    alloc();
  }

  ~SuffixArray() {
    dealloc();
  }

 private:
  int n_;
  int kmax_;
  const char *s_;
  int *sa_, *pos_, *lcp_;
  int **p_, **height_;

  void alloc() {
    sa_ = new int[n_]{};
    pos_ = new int[n_]{};
    lcp_ = new int[n_]{};

    kmax_ = 32 - __builtin_clz(n_-1);
    p_ = new int*[kmax_+1]{};
    height_ = new int*[kmax_+1]{};
    for (int i = 0; i <= kmax_; i++) {
      p_[i] = new int[n_]{};
      height_[i] = new int[n_]{};
    }
  }

  void dealloc() {
    delete[] sa_;
    delete[] pos_;
    delete[] lcp_;

    for (int i = 0; i <= kmax_; i++) {
      delete[] p_[i];
      delete[] height_[i];
    }
    delete[] p_;
    delete[] height_;
  }

  void buildSA() {
    int gap = 0;
    auto sufCmp = [pos = pos_, &gap, n = n_] (int i, int j) {
        if (pos[i] != pos[j])
          return pos[i] < pos[j];
        i += gap;
        j += gap;
        return (i < n && j < n) ? pos[i] < pos[j] : i > j;
      };
    int tmp[n_] = {0};
    REP(i, n_) sa_[i] = i, pos_[i] = s_[i];
    sort(sa_, sa_ + n_, sufCmp);
    REP(i, n_-1) tmp[i+1] = tmp[i] + sufCmp(sa_[i], sa_[i+1]);
    REP(i, n_) p_[0][sa_[i]] = tmp[i];
    for (int k = 1; k <= kmax_; k++) {
      gap = 1 << (k-1);
      sort(sa_, sa_ + n_, sufCmp);
      REP(i, n_ - 1) tmp[i + 1] = tmp[i] + sufCmp(sa_[i], sa_[i + 1]);
      REP(i, n_) pos_[sa_[i]] = tmp[i];
      REP(i, n_) p_[k][sa_[i]] = tmp[i];
    }
  }

  void buildLCP() {
    for (int i = 0, k = 0; i < n_; ++i) if (pos_[i] != n_ - 1) {
      for (int j = sa_[pos_[i] + 1]; s_[i + k] == s_[j + k];) {
        ++k;
      }
      lcp_[pos_[i]] = k;
      if (k) {
        --k;
      }
    }
  }

  void buildRMQ() {
    for (int i = 0; i < n_; i++) {
      height_[0][i] = lcp_[i];
    }
    for (int j = 1; (1<<j) < n_; j++) {
      for (int i = 0; i < n_; i++) {
        if (i + (1<<j) > n_) break;
        height_[j][i] = min(height_[j-1][i], height_[j-1][i+(1<<(j-1))]);
      }
    }
  }

  int calcLCP(int x, int y) const {
    x = pos_[x]; y = pos_[y];
    if (x > y) swap(x, y);
    int k = 0;
    while ((1<<(k+1)) < (y-x)) k++;
    return min(height_[k][x], height_[k][y-(1<<k)]);
  }

  friend class SuffixArrayTest;
};
