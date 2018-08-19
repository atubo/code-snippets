
// support query for range min
// note it's 1-indexed
class SegmentTreeMin {
    const int64_t MAXVAL = 1e12;
    int N;
    int64_t *val, *lazy;
    int *pos_;

public:
    struct QueryResult {
        int64_t value;
        int pos;
        bool operator < (const QueryResult &other) const {
            return value < other.value ||
                (value == other.value && pos < other.pos);
        }
    };

    const QueryResult NULL_RESULT{MAXVAL, -1};

    SegmentTreeMin(int N_): N(N_) {
        val = new int64_t[4*N]{};
        lazy = new int64_t[4*N]{};
        pos_ = new int[4*N]{};

        setupPosition(1, 1, N);
    }

    ~SegmentTreeMin() {
        delete[] val;
        delete[] lazy;
        delete[] pos_;
    }
    // add t to range [a, b]
    void update(int t, int a, int b) {
        update(1, t, 1, N, a, b);
    }

    // query range sum in [a, b]
    QueryResult query(int a, int b) {
        return query(1, a, b, 1, N);
    }

private:
    // initialize pos_
    void setupPosition(int k, int l, int r) {
        if (l == r) {
            pos_[k] = l;
            return;
        }

        int mid = (l + r) / 2;
        setupPosition(2*k, l, mid);
        setupPosition(2*k+1, mid+1, r);
        // assume initial values are the same
        pos_[k] = pos_[2*k];
    }

    // add t to range [a, b], current node range is [l, r]
    void update(int k, int t, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            val[k] += t;
            lazy[k] += t;
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
        int p = (val[2*k] <= val[2*k+1] ? 2*k : 2*k+1);
        val[k] = val[p];
        pos_[k] = pos_[p];
    }

    void pushDown(int k, int l, int r) {
        if (!lazy[k] || l == r) return;
        lazy[2*k] += lazy[k];
        lazy[2*k+1] += lazy[k];
        val[2*k] += lazy[k];
        val[2*k+1] += lazy[k];
        lazy[k] = 0;
    }

    // query range sum in [a, b], current node is [L, R]
    QueryResult query(int k, int a, int b, int L, int R) {
        auto ret = NULL_RESULT;
        if (!k) return ret;
        if (b < L || a > R) return ret;
        pushDown(k, L, R);
        if (a <= L && R <= b) {
            return QueryResult{val[k], pos_[k]};
        }
        int mid = (L + R) / 2;
        if (a <= mid) ret = min(ret, query(2*k, a, b, L, mid));
        if (mid < b)  ret = min(ret, query(2*k+1, a, b, mid+1, R));
        return ret;
    }
};
