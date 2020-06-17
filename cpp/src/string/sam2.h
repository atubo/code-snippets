class SuffixAutomaton {
  // state index is from 1. 0 is reserved for null
  // state n+1 is root
 public:
  int** mp;
  int ct = 0;
  int *fa;
  int *len;
  int n;
  int *id;

  SuffixAutomaton(int nn): n(nn) {
    alloc();
    for (int i = 1; i <= n; i++) {
      len[i] = i;
      id[i] = i;
    }
    ct = n + 1;
  }

  ~SuffixAutomaton() {
    dealloc();
  }

  void build(const string& s) {
    for (int i = 1; i <= n; i++) {
      extend(i, s[i-1] - 'a');
    }
  }

 private:
  void alloc() {
    int cap = 2*n + 1;
    mp = new int*[cap]{};
    for (int i = 0; i < cap; i++) {
      mp[i] = new int[26]{};
    }
    fa = new int[cap]{};
    len = new int[cap]{};
    id = new int[cap]{};
  }

  void dealloc() {
    for (int i = 0; i < 2*n+1; i++) {
      delete[] mp[i];
    }
    delete[] mp;
    delete[] fa;
    delete[] len;
    delete[] id;
  }

  void extend(int x, int c) {
    // index x is from 1
    int p = (x == 1) ? n+1 : x-1;
    for (; p && mp[p][c] == 0; p = fa[p]) mp[p][c] = x;
    if (p == 0) {
      fa[x] = n + 1;
      return;
    }
    int q = mp[p][c];
    if (len[q] == len[p] + 1) {
      fa[x] = q;
      return;
    }
    len[++ct] = len[p] + 1;
    id[ct] = id[q];
    for (int i = 0; i < 26; i++) {
      mp[ct][i] = mp[q][i];
    }
    for (; p && mp[p][c] == q; p = fa[p]) {
      mp[p][c] = ct;
    }
    fa[ct] = fa[q];
    fa[q] = fa[x] = ct;
  }
};
