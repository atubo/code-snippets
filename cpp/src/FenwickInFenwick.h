// note row and col are 1-indexed here
class FenwickInFenwick {
public:
    const int N, M;
    int **root;

    FenwickInFenwick(int N_, int M_): N(N_), M(M_) {
        alloc();
    }

    ~FenwickInFenwick() {
        dealloc();
    }

    // add value t to (x, y)
    void add(int x, int y, int t) {
        for (int i = x; i <= N; i += lowbit(i)) {
            addRow(i, y, t);
        }
    }

    // weight sum in region (x1, y1) -> (x2, y2), inclusive
    int query(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - query(x1-1, y1) - query(x2, y1-1) +
            query(x1-1, y1-1);
    }

private:
    void alloc() {
        root = new int*[N+1];
        for (int i = 0; i <= N; i++) {
            root[i] = new int[M+1]{};
        }
    }

    void dealloc() {
        for (int i = 0; i <= N; i++) {
            delete[] root[i];
        }
        delete[] root;
    }

    int lowbit(int x) const {return x & -x;}

    void addRow(int row, int y, int t) {
        for (int i = y; i <= M; i += lowbit(i)) {
            root[row][i] += t;
        }
    }

    // query range (1, 1) -> (x, y) inclusive
    int query(int x, int y) const {
        if (x == 0) return 0;
        int res = 0;
        while (x) {
            res += queryRow(x, y);
            x -= lowbit(x);
        }
        return res;
    }

    int queryRow(int row, int y) const {
        if (y == 0) return 0;
        int res = 0;
        while (y) {
            res += root[row][y];
            y -= lowbit(y);
        }
        return res;
    }
};
