
class Ntt2 {
 public:
  // get the first power of 2 that is larger than n
  static int getlen(int n) {
    return 1 << (32 - __builtin_clz(n));
  }

  // n must be highest possible n in ntt function calls
  Ntt2(int p, int g, int n) : p_(p), g_(g) {
    cap_ = getlen(2*n);
    alloc();
    init();
  }

  ~Ntt2() {
    dealloc();
  }

  void ntt(int* a, int op, int n) const {
    // length must be power of 2
    assert(__builtin_popcount(n) == 1);
    int j = 0;
    for (int i = 0; i < n; i++) {
      if (j > i) {
        swap(a[i], a[j]);
      }
      int m = (n >> 1);
      while (m >= 2 && j >= m) {
        j -= m;
        m >>= 1;
      }
      j += m;
    }

    for (int i = 1; i < n; i<<=1) {
      for (j = 0; j < n; j+=i<<1) {
        for (int k = 0; k < i; k++) {
          int64_t t = (op == 1 ? 1LL*w_[2*i+k] : 1LL*w_[4*i-k]) * a[i+j+k] % p_;
          a[i+j+k] = (a[j+k]-t+p_)%p_;
          a[j+k] = (a[j+k]+t)%p_;
        }
      }
    }

    if (op == -1) {
      int64_t inv = p_ - (p_ - 1) / n;
      for (int i = 0; i < n; i++) a[i] = a[i] * inv % p_;
    }
  }

  // length of a and b must be power of 2 and >= 2*n
  // b must be initialized to 0 before calling
  void inverse(const int *a, int *b, int n) const {
    if (n == 1) {
      b[0] = pow(a[0], p_-2);
      return;
    }
    inverse(a, b, (n+1)/2);
    int lim = 1;
    while (lim < 2*n) lim <<= 1;
    memcpy(temp_, a, n * sizeof(int));
    memset(temp_+n, 0, (lim-n) * sizeof(int));
    ntt(temp_, 1, lim);
    ntt(b, 1, lim);
    for (int i = 0; i < lim; i++) {
      temp_[i] = 1LL * b[i] * (2 - 1LL * b[i] * temp_[i] % p_ + p_) % p_;
    }
    ntt(temp_, -1, lim);
    memcpy(b, temp_, n * sizeof(int));
    memset(b+n, 0, (lim-n) * sizeof(int));
  }

  int pow(int64_t x, int y) const {
    int64_t ans = 1;
    while (y) {
      if (y & 1) ans = ans * x % p_;
      x = x * x % p_;
      y >>= 1;
    }
    return ans;
  }

 private:
  int p_, g_;
  int cap_;
  int* temp_;
  int* w_;

  void alloc() {
    temp_ = new int[cap_]{};
    w_ = new int[cap_]{};
  }

  void dealloc() {
    delete[] temp_;
    delete[] w_;
  }

  void init() {
    // initialize the powers of g
    // if p = c * 2^k + 1
    // w[i] = 1 if i is power of 2
    // w[i] = g ^ (j * c * 2 ^ (k - n)) if i = j + 2^n
    int n = __builtin_ctz(cap_ >> 1);
    w_[1<<n] = 1;
    int wn = pow(g_, (p_-1) >> n);
    for (int i = (1<<n)+1; i < cap_; i++) {
      w_[i] = (1LL * w_[i-1] * wn) % p_;
    }
    for (int i = (1<<n)-1; i; --i) {
      w_[i] = w_[i<<1];
    }
  }

};
