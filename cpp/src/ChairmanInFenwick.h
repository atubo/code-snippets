struct ChairmanInFenwick {
    struct Node {
        Node() : L(0), R(0), sum(0) {}
        // note L and R are children's index, not query range
        int L, R, sum;
    };

    int N;  // number of positions, index is 1-based
    int M;  // number of weights, index is 0-based
    int T_cnt;
    int *root;
    int *val, *lc, *rc;

    // cap is the number of elements to be added
    ChairmanInFenwick(int N_, int M_, int cap): N(N_), M(M_), T_cnt(1) {
        root = new int[N+1]{};
        const int numOfNodes = cap * int(log2(N)+1) * int(log2(M)+1);
        val = new int[numOfNodes]{};
        lc = new int[numOfNodes]{};
        rc = new int[numOfNodes]{};
    }

    ~ChairmanInFenwick() {
        delete[] root;
        delete[] val;
        delete[] lc;
        delete[] rc;
    }

    int lowbit(int x) {return x & -x;}

    // add value t to weight node w at position x
    void add(int x, int w, int t) {
        for (int i = x; i <= N; i += lowbit(i)) {
            update(root[i], w, t, 0, M-1);
        }
    }

    void update(int &now, int w, int t, int l, int r) {
        if (!now) now = T_cnt++;
        val[now] += t;
        if (l == r) return;
        int mid = (l + r) / 2;
        if (w <= mid) update(lc[now], w, t, l, mid);
        else          update(rc[now], w, t, mid+1, r);
    }

    // weight sum [l, r] for position [1, k]
    int query(int k, int l, int r) {
        if (l > r) return 0;
        int sum = 0;
        for (int j = k; j; j -= lowbit(j)) {
            sum += querySingleTree(root[j], 0, M-1, l, r);
        }
        return sum;
    }

    int querySingleTree(int node, int L, int R, int l, int r) {
        if (L >= l && R <= r) return val[node];
        if (L > r || R < l) return 0;
        int sum = 0;
        int mid = (L + R) / 2;
        if (l <= mid) sum += querySingleTree(lc[node], L, mid, l, r);
        if (mid < r)  sum += querySingleTree(rc[node], mid+1, R, l, r);
        return sum;
    }
};

