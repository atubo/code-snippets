
template<short K>
struct PointT {
    int x[K], w;
};

// dynamically rebalance
template<short K>
class KdTree3 {
    friend class KdTree3Test;
public:
    using Point = PointT<K>;
    struct Cmp {
        Cmp(int d): idx(d) {}
        bool operator () (const Point &a, const Point &b) const {
            return a.x[idx] < b.x[idx];
        }
        int idx;
    };

    KdTree3(int n): n_(n) {
        alloc();
        for (int i = 0; i < K; i++) {
            max_[i][0] = INT_MIN;
            min_[i][0] = INT_MAX;
        }
    }

    ~KdTree3() {
        dealloc();
    }

    void insert(const Point &p) {
        auto bad = insert(root_, p, 0);
        if (bad.first) rebuild(bad);
    }

    void print() const {
        print('r', root_, 0);
    }

private:
    constexpr static double alpha = 0.75;
    const int n_;
    int *lc_, *rc_;
    int *size_, *maxwt_;
    int *max_[K], *min_[K];
    Point *d_;  // point on the node
    int curr_ = 0;
    int root_ = 0;

    void alloc() {
        const int np = n_+1;
        lc_ = new int[np]{};
        rc_ = new int[np]{};
        size_ = new int[np]{};
        maxwt_ = new int[np]{};
        for (int i = 0; i < K; i++) {
            max_[i] = new int[np]{};
            min_[i] = new int[np]{};
        }
        d_ = new Point[np]{};
    }

    void dealloc() {
        delete[] lc_;
        delete[] rc_;
        delete[] size_;
        delete[] maxwt_;
        for (int i = 0; i < K; i++) {
            delete[] max_[i];
            delete[] min_[i];
        }
        delete[] d_;
    }

    void pushup(int k) {
        int lc = lc_[k], rc = rc_[k];
        size_[k] = 1 + size_[lc] + size_[rc];
        maxwt_[k] = max(max(maxwt_[lc], maxwt_[rc]), d_[k].w);
        for (int i = 0; i < K; i++) {
            max_[i][k] = max(max(max_[i][lc], max_[i][rc]), d_[k].x[i]);
            min_[i][k] = min(min(min_[i][lc], min_[i][rc]), d_[k].x[i]);
        }
    }

    bool unbalanced(int k) const {
        int lc = lc_[k], rc = rc_[k];
        return size_[lc] > size_[k]*alpha ||
            size_[rc] > size_[k]*alpha;
    }

    void setLeaf(int k) {
        lc_[k] = rc_[k] = 0;
        for (int i = 0; i < K; i++) {
            max_[i][k] = min_[i][k] = d_[k].x[i];
        }
        maxwt_[k] = d_[k].w;
    }

    void spawn(int &k, const Point &p) {
        k = ++curr_;
        d_[k] = p;
        setLeaf(k);
        pushup(k);
    }

    pair<int*, int> insert(int &k, const Point &p, int d) {
        if (k == 0) {
            spawn(k, p);
            return make_pair((int*)NULL, d);
        }
        int &c = p.x[d] < d_[k].x[d] ? lc_[k] : rc_[k]; 
        auto bad = insert(c, p, (d+1)%K);
        pushup(k);
        if (unbalanced(k)) {
            bad = make_pair(&k, d);
        }
        return bad;
    }

    void traverse(int k, vector<Point> &p, vector<int> &idx) {
        if (k == 0) return;
        p.push_back(d_[k]);
        idx.push_back(k);
        traverse(lc_[k], p, idx);
        traverse(rc_[k], p, idx);
    }

    int build(int l, int r, int d, vector<Point> &p,
               const vector<int> &idx, int &curr) {
        if (l > r) return 0;
        int mid = (l + r) / 2;
        nth_element(p.begin()+l, p.begin()+mid, p.begin()+r+1, Cmp(d));
        d_[idx[curr++]] = p[mid];
        int k = idx[curr-1];
        if (l == r) {
            setLeaf(k);
            return k;
        }
        lc_[k] = build(l, mid-1, (d+1)%K, p, idx, curr);
        rc_[k] = build(mid+1, r, (d+1)%K, p, idx, curr);
        pushup(k);
        return k;
    }

    void rebuild(const pair<int*, int> &bad) {
        int k = *bad.first;
        int d = bad.second;
        vector<int> idx;
        vector<Point> pts;
        traverse(k, pts, idx);
        int curr = 0;
        build(0, pts.size()-1, d, pts, idx, curr);
    }

    void printArray(int *a) const {
        printf("(");
        for (int i = 0; i < K-1; i++) {
            printf("%d ", a[i]);
        }
        printf("%d)", a[K-1]);
    }

    void printMinMax(int * const *a, int k) const {
        printf("(");
        for (int i = 0; i < K-1; i++) {
            printf("%d ", a[i][k]);
        }
        printf("%d)", a[K-1][k]);
    }

    void print(char c, int k, int d) const {
        printf("%c ", c);
        for (int i = 0; i < d; i++) {
            printf(" ");
        }
        printf("k=%d ", k);
        printArray(d_[k].x);
        printf(" max: ");
        printMinMax(max_, k);
        printf(" min: ");
        printMinMax(min_, k);
        printf(" mw: %d\n", maxwt_[k]);
        if (lc_[k]) print('l', lc_[k], d+1);
        if (rc_[k]) print('r', rc_[k], d+1);
    }
};
