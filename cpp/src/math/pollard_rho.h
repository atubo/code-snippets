
class PollardRho {
 public:
  PollardRho(): millerRabin_(20, 1) {}

  vector<int64_t> factorize(int64_t n) const {
    vector<int64_t> ret;
    factorize(n, 107, ret);
    sort(ret.begin(), ret.end());
    return ret;
  }

 private:
  MillerRabin millerRabin_;

  void factorize(int64_t n, int k, vector<int64_t>& factors) const {
    if (n == 1) return;
    if (millerRabin_.check(n)) {
      factors.push_back(n);
      return;
    }
    int c = k;
    int64_t p = n;
    while (p >= n) {
      p = rho(p, c--);
    }
    factorize(p, k, factors);
    factorize(n/p, k, factors);
  }

  int64_t rho(int64_t x, int c) const {
    int64_t p = rand()%(x-1) + 1;
    int64_t q = p;
    while (true) {
      p = (MillerRabin::mult_mod(p, p, x) + c) % x;
      q = (MillerRabin::mult_mod(q, q, x) + c) % x;
      q = (MillerRabin::mult_mod(q, q, x) + c) % x;
      int64_t d = gcd(abs(q-p), x);
      if (d != 1) return d;
      if (d == 0) return x;
    }
    return x;
  }

  static int64_t gcd(int64_t a, int64_t b) {
    if (b == 0) return a;
    return gcd(b, a%b);
  }
};
