// For the cases that we need to create a lot of segment trees
// but the total number of nodes is limited

class SegmentForest {
    struct Node {
        // L and R are indices of its children
        // real left and right boundaries are not kept in the node itself
        int L = 0, R = 0;
        int sum = 0;
    };

    int N;  // number of trees, 0-indexed
    int M;  // number of leaves of each tree, 0-indexed

    int *root;
    Node *T;
    int T_cnt = 1;

public:
    SegmentForest(int N_, int M_, int numInsertions): N(N_), M(M_) {
        root = new int[N]{};

        // T[0] is null node, so we add 1
        int cap = 1 + numInsertions * int(log2(M) + 2);
        T = new Node[cap]{};
    }

    ~SegmentForest() {
        delete[] root;
        delete[] T;
    }

    // add t to position x of tree rootIndex
    void insert(int rootIndex, int x, int t) {
        insert(root[rootIndex], x, t, 0, M-1);
    }

    // query in range [start, end]
    int query(int rootIndex, int start, int end) const {
        return query(root[rootIndex], start, end, 0, M-1);
    }

private:
    // insert a new node x with value t
    // curret range is [l, r]
    void insert(int &now, int x, int t, int l, int r) {
        if (!now) now = T_cnt++;
        T[now].sum += t;
        if (l == r) return;
        int mid = (l + r) / 2;
        if (x <= mid) insert(T[now].L, x, t, l, mid);
        else          insert(T[now].R, x, t, mid+1, r);
    }

    int query(int node, int start, int end, int l, int r) const {
        if (node == 0) return 0;
        if (l > r) return 0;
        if (start <= l && r <= end) return T[node].sum;
        int mid = (l + r) / 2;
        int ret = 0;
        if (start <= mid) ret += query(T[node].L, start, end, l, mid);
        if (mid+1 <= end) ret += query(T[node].R, start, end, mid+1, r);
        return ret;
    }
};
