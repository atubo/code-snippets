
namespace discrete_logarithm {

// (g, x, y) that a*x + b*y = g
void ext_gcd(int64_t a, int64_t b, int64_t &g, int64_t &x, int64_t &y) {
    if (b == 0) {
        g = a; x = 1; y = 0;
        return;
    }
    int64_t dp, xp, yp;
    ext_gcd(b, a % b, dp, xp, yp);
    g = dp;
    x = yp;
    y = xp - a / b * yp;
}

// find x that a*x = b mod n
int64_t mod_solve(int64_t a, int64_t b, int n) {
    int64_t d, xp, yp;
    ext_gcd(a, n, d, xp, yp);
    if (b % d == 0) {
        int64_t x0 = (xp * (b / d) % n + n) % n;
        return x0;
    } else {
        abort();
    }
}

// precondition:
// 1. gcd(a, p) = 1
// 2. 0 <= a < p and 0 <= b < p
int babystepGiantstep(int a, int b, int p) {
  const int n = p - 1;
  const int m = int(sqrt(n) + 1);
  unordered_map<int, int> table;
  int t = 1; // t is a^j for j in [0, m)
  for (int j = 0; j < m; j++) {
    if (table.find(t) == table.end()) {
      table[t] = j;
    }
    t = (1LL * t * a) % p;
  }
  t = mod_solve(t, 1, p); // now t is a^(-m)
  int gamma = b; // gamma = b * a^(-im)
  for (int i = 0; i < m; i++) {
    auto it = table.find(gamma);
    if (it != table.end()) {
      return (i * m + it->second) % n;
    }
    gamma = (1LL * gamma * t) % p;
  }
  return -1;
}

int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a%b);
}

int extBsgs(int a, int b, int p) {
  if (a == 0) return b == 0 ? 1 : -1;
  if (b == 1) return 0;
  int g = gcd(a, p);
  if (g == 1) return babystepGiantstep(a, b, p);
  if (b % g != 0) return -1;
  int t = mod_solve(a/g, 1, p/g);
  int x = extBsgs(a, 1LL * b/g * t % (p/g), p/g);
  return (x == -1 ? -1 : x + 1);
}
}
