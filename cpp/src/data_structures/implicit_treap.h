// https://threads-iiith.quora.com/Treaps-One-Tree-to-Rule-em-all-Part-2

// 1-indexed, 0 means null
class ImplicitTreap {
    struct Node {
        int prior, size;
        int val;  // value stored in the array
        int sum;  // whatever info you want to maintain in segtree for the node
        int lazy; // whatever lazy update you want to do
        int l, r;
    };
public:
    ImplicitTreap(int cap): cap_(cap) {
        alloc();
    }

    ~ImplicitTreap() {
        dealloc();
    }

    /**
     * Note a should also be 1-indexed
     * @param a: the array based on which the treap is built
     * @return: root index
     */
    int build(const vector<int>& a) {
        root_ = build(a, 1, a.size());
        return root_;
    }

    int rangeQuery(int l, int r) { // [l,r]
        int t = root_;
        int L, mid, R;
        split(t, L, mid, l-1);
        split(mid, t, R, r-l+1);
        int ans = nodes_[t].sum;
        merge(mid, L, t);
        merge(root_, mid, R);
        return ans;
    }

    void rangeUpdate(int l, int r, int val) { // [l,r]
        int t = root_;
        int L, mid, R;
        split(t, L, mid, l-1);
        split(mid, t, R, r-l+1);
        nodes_[t].lazy += val;
        merge(mid, L, t);
        merge(root_, mid, R);
    }

    int operator[](int n) const {
        assert(1 <= n && n <= sz(root_));
        int t = root_;
        while (true) {
            int left_cnt = sz(nodes_[t].l);
            if (left_cnt == n-1) return nodes_[t].val;
            else if (left_cnt < n-1) {
                t = nodes_[t].r;
                n -= left_cnt + 1;
            } else {
                t = nodes_[t].l;
            }
        }
        assert(false);
        return -1;
    }

    /**
     * insert val after position pos, if pos = 0, insert at the begining
     * @param pos: position
     * @param val: value
     */
    void insert(int pos, int val) {
        assert(0 <= pos && pos <= sz(root_));
        int newnode = allocNode(val);
        if (pos == 0) {
            merge(root_, newnode, root_);
        } else if (pos == sz(root_)) {
            merge(root_, root_, newnode);
        } else {
            int t = root_;
            int L, R;
            split(t, L, R, pos);
            merge(t, L, newnode);
            merge(root_, t, R);
        }
    }

private:
    int cap_;
    int curr_ = 1;
    int root_;
    Node *nodes_;

    void alloc() {
        nodes_ = new Node[cap_+1]{};
    }

    void dealloc() {
        delete[] nodes_;
    }

    int sz(int t) const {
        return t ? nodes_[t].size : 0;
    }

    void reset(int t) {
        // no need to reset lazy coz when we call this lazy would
        // itself be propagated
        if (t) nodes_[t].sum = nodes_[t].val;
    }

    // combining two ranges of segtree
    void combine(int t, int l, int r) {
        nodes_[t].sum = nodes_[l].sum + nodes_[r].sum + nodes_[t].val;
    }

    void pushUp(int t) {
        if (!t) return;
        Node &node = nodes_[t];
        node.size = sz(node.l) + 1 + sz(node.r);
        // reset the value of current node assuming it now represents
        // a single element of the array
        reset(t);
        // propaget lazy before combining
        pushDown(node.l);
        pushDown(node.r);
        combine(t, node.l, node.r);
    }

    // invariant: values are right after lazy is pushed down
    void pushDown(int t) {
        if (!t || !nodes_[t].lazy) return;
        Node &node = nodes_[t];
        // operation of lazy
        node.val += node.lazy;
        node.sum += node.lazy * sz(t);
        // propagate lazy
        if (node.l) nodes_[node.l].lazy += node.lazy;
        if (node.r) nodes_[node.r].lazy += node.lazy;
        node.lazy = 0;
    }


    // l -> leftarray, r->rightarray
    void merge(int& t, int l, int r) {
        pushDown(l);
        pushDown(r);
        Node &nl = nodes_[l];
        Node &nr = nodes_[r];
        if (!l || !r) t = l ? l : r;
        else if (nl.prior > nr.prior) merge(nl.r, nl.r, r), t=l;
        else merge(nr.l, l, nr.l), t=r;
        pushUp(t);
    }

    // [1, pos] goes to the left tree, remaining goes to the right
    void split(int t, int& l, int& r, int pos, int add=0) {
        if (!t) {l = r = 0; return;}
        pushDown(t);
        Node &node = nodes_[t];
        int curr_pos = add + sz(node.l);
        if (curr_pos < pos) { // element at pos goes to left subtree
            split(node.r, node.r, r, pos, curr_pos+1);
            l = t;
        } else {
            split(node.l, l, node.l, pos, add);
            r = t;
        }
        pushUp(t);
    }

    /**
     * create a node from the memory pool
     * @param val: value of the node
     * @return: node index
     */
    int allocNode(int val) {
        Node& node = nodes_[curr_];
        node.prior = rand();
        node.size = 1;
        node.val = val;
        node.sum = val;
        node.lazy = 0;
        node.l = node.r = 0;
        return curr_++;
    }

    int build(const vector<int>& a, int i, int j) {
        // [i, j)
        if (i == j-1) {
            return allocNode(a[i]);
        }
        int mid = (i+j)/2;
        int left = build(a, i, mid);
        int right = build(a, mid, j);
        int ret;
        merge(ret, left, right);
        return ret;
    }
};
