const int MAXN = 500010;

struct ChairmanTree {
    struct Node {
        // L and R are indices of its children
        // real left and right boundaries are not kept in the node
        // to save memory
        int L, R;
        int sum;

        Node(): L(0), R(0), sum(0) {}
    };

    int N; // number of positions, index is 1-based
    int M; // number of weights, index is 1-based
    int T_cnt;

    // use static to avoid dynamic memory management
    static int root[MAXN];
    static Node T[MAXN*21];

    ChairmanTree(int N_, int M_): N(N_), M(M_), T_cnt(1) {}

    // insert a new weight node x with value t
    // current range is [l, r]
    void insert(int &now, int x, int t, int l, int r) {
        T[T_cnt++] = T[now];
        now = T_cnt-1;
        T[now].sum += t;
        if (l == r) return;
        int mid = (l + r) / 2;
        if (x <= mid) insert(T[now].L, x, t, l, mid);
        else          insert(T[now].R, x, t, mid+1, r);
    }

    // for user's convenience
    void insert(int &now, int from, int x, int t) {
        now = from;
        insert(now, x, t, 1, M);
    }
};

using Node = ChairmanTree::Node;
int ChairmanTree::root[MAXN];
Node ChairmanTree::T[MAXN*21];
