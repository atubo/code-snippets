
class MillerRabin {
 public:
  MillerRabin(int S, unsigned int seed=0) : S_(S) {
    if (seed == 0) {
      srand(time(NULL));
    } else {
      srand(seed);
    }
  }

  bool check(int64_t n) const {
    if (n < 2) return false;
    if (n == 2) return true;
    if ((n&1) == 0) return false;
    int64_t x = n-1;
    int t = 0;
    while ((x&1) == 0) {
      x >>= 1;
      t++;
    }

    for (int i = 0; i < S_; i++) {
      int64_t a = rand()%(n-1) + 1;
      if (!check(a, n, x, t)) {
        return false;
      }
    }
    return true;
  }

  static int64_t mult_mod(int64_t a, int64_t b, int64_t mod) {
    a %= mod;
    b %= mod;
    int64_t ret = 0;
    int64_t x = a;
    while (b) {
      if (b & 1) {
        ret += x;
        if (ret >= mod) ret -= mod;
      }
      x <<= 1;
      if (x >= mod) x -= mod;
      b >>= 1;
    }
    return ret;
  }

 private:
  // check a^(n-1) = 1 mod n
  // n-1 = x * 2^t
  // return true if it passes the test
  static bool check(int64_t a, int64_t n, int64_t x, int t) {
    int64_t ret = pow_mod(a, x, n);
    int64_t last = ret;
    for (int i = 1; i <= t; i++) {
      ret = mult_mod(ret, ret, n);
      if (ret == 1 && last != 1 && last != n-1) return false;
      last = ret;
    }
    return ret == 1;
  }

  static int64_t pow_mod(int64_t a, int64_t n, int64_t mod) {
    int64_t ret = 1;
    int64_t x = a % mod;
    while (n) {
      if (n & 1) ret = mult_mod(ret, x, mod);
      x = mult_mod(x, x, mod);
      n >>= 1;
    }
    return ret;
  }

  const int S_;
};
