class BIT {
public:
    // 1-indexed
    BIT(int size): N(size) {
        tree = (int64_t*)malloc((size+1) * sizeof(int64_t));
        clear();
    }

    ~BIT() {
        free(tree);
        tree = NULL;
    }

    void clear() {
        memset(tree, 0, (N+1) * sizeof(int64_t));
    }

    // add v to value at x
    void set(int x, int v) {
        while(x <= N) {
            tree[x] += v;
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int64_t get(int x) const {
        int64_t res = 0;
        while(x) {
            res += tree[x];
            x -= (x & -x);
        }
        return res;
    }

    // get result for [x, y]
    int64_t get(int x, int y) const {
        return get(y) - (x > 1 ? get(x-1) : 0);
    }

    // index of first element with cumulative sum >= x
    // note it returns 0 for x = 0
    int lowerBound(int64_t x) {
        return bound(x, true);
    }

    int upperBound(int64_t x) {
        return bound(x, false);
    }

private:
    int64_t* tree;
    const int N;

    int bound(int64_t x, bool is_lower) {
        int clz = __builtin_clz(N);
        int idx = 0, mask = 1 << (31 - clz);     // first power of 2 <= N
        while (mask) {
            int t = idx + mask;
            if (t <= N && x >= tree[t]) {
                idx = t;
                x -= tree[t];
            }
            mask >>= 1;
        }
        if (is_lower) return x == 0 ? idx : idx+1;
        else return idx+1;
    }
};
