namespace math {

class Cantor {
 public:
  // members in [0, n-1]
  static int64_t encode(const vector<int>& a) {
    int64_t ret = 0;
    int64_t fac = 1;
    const int n = a.size();
    vector<bool> seen(n, false);
    for (int i = n-1; i >= 0; i--) {
      int x = a[i];
      int k = count(x, seen);
      seen[x] = true;
      ret += k * fac;
      fac *= (n-i);
    }
    return ret;
  }

  static vector<int> decode(int64_t code, int n) {
    vector<int64_t> fac(n);
    fac[0] = 1;
    for (int i = 1; i < n; i++) {
      fac[i] = fac[i-1] * i;
    }

    vector<int> ret(n);
    vector<bool> seen(n, false);
    for (int i = 0; i < n; i++) {
      int x = code / fac[n-1-i];
      code = code % fac[n-1-i];
      ret[i] = nth(x, seen);
      seen[ret[i]] = true;
    }
    return ret;
  }

 private:
  static int count(int x, const vector<bool>& seen) {
    int ret = 0;
    for (int y = 0; y < x; y++) {
      ret += seen[y];
    }
    return ret;
  }

  static int nth(int x, const vector<bool>& seen) {
    int c = 0;
    int y = 0;
    while (c < x) {
      c += (!seen[y++]);
    }
    while (seen[y]) y++;
    return y;
  }
};
} // namespace math
