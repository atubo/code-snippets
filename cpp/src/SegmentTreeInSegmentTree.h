// 1-indexed
class SegmentTreeInSegmentTree {
private:
    struct Node {
        Node(): left(0), right(0), maxVal(INT_MIN) {}
        int left, right, maxVal;
    };

    const int N, M;
    Node *nodes;
    int  *roots;
    int nodeCnt;
public:
    // N, and M need to be ceiled to the next power of 2
    SegmentTreeInSegmentTree(int N_, int M_): N(N_), M(M_) {
        nodes = new Node[2*N*2*M]{};
        roots = new int[2*N]{};
        nodeCnt = 1;
    }

    ~SegmentTreeInSegmentTree() {
        delete[] roots;
        delete[] nodes;
    }

    // put val to (x, y)
    void put(int val, int x, int y) {
        put(1, val, x, 1, N, y);
    }

    int query(int x1, int x2, int y1, int y2) {
        return query(1, x1, x2, 1, N, y1, y2);
    }

private:
    // put val to (x, y), currently at root[k]
    // x range for the tree at this root is [lx, rx]
    void put(int k, int val,
             int x, int lx, int rx,
             int y) {
        if (x < lx || rx < x) return;
        update(roots[k], val, y, 1, M);
        if (lx == rx) return;
        int mid = (lx + rx) / 2;
        if (x <= mid) put(2*k,   val, x, lx,    mid, y);
        else          put(2*k+1, val, x, mid+1, rx,  y);
    }

    // put val to position y, current node range is [l, r]
    void update(int &now, int val, int y, int l, int r) {
        if (y < l || r < y) return;
        if (!now) now = nodeCnt++;
        if (l == r) {
            nodes[now].maxVal = val;
            return;
        }
        int mid = (l + r) / 2;
        if (y <= mid) update(nodes[now].left,  val, y, l, mid);
        else          update(nodes[now].right, val, y, mid+1, r);
        nodes[now].maxVal = max(nodes[nodes[now].left].maxVal,
                                nodes[nodes[now].right].maxVal);
    }

    int query(int k, int x1, int x2, int lx, int rx, int y1, int y2) {
        assert(x1 <= x2);
        if (x2 < lx || rx < x1) return INT_MIN;
        if (lx >= x1 && rx <= x2) return query(roots[k], y1, y2, 1, M);
        int mid = (lx + rx) / 2;
        int ret = INT_MIN;
        if (x1 <= mid) ret = query(2*k, x1, x2, lx, mid, y1, y2);
        if (mid < x2)  ret = max(ret, query(2*k+1, x1, x2, mid+1, rx, y1, y2));
        return ret;
    }

    int query(int node, int y1, int y2, int l, int r) {
        assert(y1 <= y2);
        if (y2 < l || r < y1) return INT_MIN;
        if (l >= y1 && r <= y2) return nodes[node].maxVal;
        int mid = (l + r) / 2;
        int ret = INT_MIN;
        if (y1 <= mid) ret = query(nodes[node].left, y1, y2, l, mid);
        if (mid < y2)  ret = max(ret, query(nodes[node].right, y1, y2, mid+1, r));
        return ret;
    }
};
