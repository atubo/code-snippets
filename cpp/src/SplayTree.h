
// index starts from 1 (0 is for NULL)
class SplayTree {
public:

    SplayTree(int size) {
        // 1-indexed
        N = size;
        f.resize(N + 1);
        t.resize(N + 1);
        sz.resize(N + 1);
        tag.resize(N + 1);
        for (int i = 0; i <= N; i++) {
            t[i][0] = t[i][1] = 0;
        }
        root = build(1, N, 0);
    }

    // build range [i, j]
    int build(int p, int q, int fa) {
        assert(q - p >= 0);

        int mid = (p + q) / 2;
        f[mid] = fa;

        if (mid - p >= 1) t[mid][0] = build(p, mid-1, mid);
        if (q - mid >= 1) t[mid][1] = build(mid+1, q, mid);

        update(mid);

        return mid;
    }

    void reverse(int x) {
        tag[x] ^= 1;
        swap(t[x][0], t[x][1]);
    }

    void pushDown(int x) {
        if (tag[x]) {
            if (t[x][0]) reverse(t[x][0]);
            if (t[x][1]) reverse(t[x][1]);
            tag[x] = 0;
        }
    }

    void update(int x) {
        assert(x);
    
        sz[x] = sz[t[x][0]] + sz[t[x][1]] + 1;
    }

    bool son(int x) const {
        return t[f[x]][0] == x ? 0 : 1;
    }

    void rotate(int x) {
        int y = f[x], z = son(x);

        t[y][z] = t[x][1-z];
        if (t[x][1-z]) f[t[x][1-z]] = y;

        f[x] = f[y];
        if (f[x]) t[f[x]][son(y)] = x;

        f[y] = x; t[x][1-z] = y;
        update(y); update(x);
    }

    void propagate(int x, int y) {
        if (x == y) return;
        stack<int> d;
        do {
            d.push(x);
            x = f[x];
        } while (x != y);
        while (!d.empty()) {
            x = d.top();
            d.pop();
            pushDown(x);
        }
    }

    void splay(int x, int y) {
        propagate(x, y);
        while (f[x] != y) {
            if (f[f[x]] != y) {
                if (son(f[x]) == son(x)) rotate(f[x]);
                else rotate(x);
            }
            rotate(x);
        }
        if (!y) root = x;
    }

    // find k-th element (starting from 1)
    int find_by_order(int k) {
        assert(1 <= k && k <= N);
        int x = root;
        while (true) {
            pushDown(x);
            if (sz[t[x][0]] == k-1) return x;
            if (sz[t[x][0]] < k-1) {
                k -= sz[t[x][0]] + 1;
                x = t[x][1];
            } else {
                x = t[x][0];
            }
        }
        assert(false);
        return x;
    }

    void print() {
        printf("f: ");
        for (int i = 0; i <= N; i++) {
            printf("%d ", f[i]);
        }
        printf("t: ");
        for (int i = 0; i <= N; i++) {
            printf("(%d %d) ", t[i][0], t[i][1]);
        }
        printf("sz: ");
        for (int i = 0; i <= N; i++) {
            printf("%d ", sz[i]);
        }
        printf("tag: ");
        for (int i = 0; i <= N; i++) {
            printf("%d ", tag[i]);
        }
        printf("root: %d", root);
               
        printf("\n");
    }

    int root;
    int N;  // number of elements, 0 (NULL) excluded
    vector<int> f;
    vector<array<int, 2>> t;
    vector<int> sz;
    vector<int> tag;
};

