// https://threads-iiith.quora.com/Treaps-One-Tree-to-Rule-em-all-Part-2
#include <stddef.h>
#include <stdlib.h>
#include <vector>

using namespace std;

namespace ImplicitTreap {
    struct Node {
        int prior, size;
        int val;  // value stored in the array
        int sum;  // whatever info you want to maintain in segtree for the node
        int lazy; // whatever lazy update you want to do
        struct Node *l, *r;
    };
    typedef Node* NodePtr;

    int sz(NodePtr t) {
        return t ? t->size : 0;
    }

    void upd_sz(NodePtr t) {
        if (t) t->size = sz(t->l) + 1 + sz(t->r);
    }

    void lazy(NodePtr t) {
        if (!t || !t->lazy) return;
        // operation of lazy
        t->val += t->lazy;
        t->sum += t->lazy * sz(t);
        // propagate lazy
        if (t->l) t->l->lazy += t->lazy;
        if (t->r) t->r->lazy += t->lazy;
        t->lazy = 0;
    }

    void reset(NodePtr t) {
        // no need to reset lazy coz when we call this lazy would
        // itself be propagated
        if (t) t->sum = t->val;
    }

    // combining two ranges of segtree
    void combine(NodePtr& t, NodePtr l, NodePtr r) {
        if (!l || !r) {
            t = (l ? l : r);
            return;
        }
        t->sum = l->sum + r->sum;
    }

    // operation of segtree
    void operation(NodePtr t) {
        if (!t) return;
        // reset the value of current node assuming it now represents
        // a single element of the array
        reset(t);
        // propaget lazy before combining
        lazy(t->l);
        lazy(t->r);
        combine(t, t->l, t);
        combine(t, t, t->r);
    }

    void split(NodePtr t, NodePtr& l, NodePtr& r, int pos, int add=0) {
        if (!t) {l = r = NULL; return;}
        lazy(t);
        int curr_pos = add + sz(t->l);
        if (curr_pos <= pos) { // element at pos goes to left subtree
            split(t->r, t->r, r, pos, curr_pos+1);
            l = t;
        } else {
            split(t->l, l, t->l, pos, add);
            r = t;
        }
        upd_sz(t);
        operation(t);
    }

    // l -> leftarray, r->rightarray
    void merge(NodePtr& t, NodePtr l, NodePtr r) {
        lazy(l);
        lazy(r);
        if (!l || !r) t = l ? l : r;
        else if (l->prior > r->prior) merge(l->r, l->r, r), t=l;
        else merge(r->l, l, r->l), t=r;
        upd_sz(t);
        operation(t);
    }

    NodePtr init(int val) {
        NodePtr ret = (NodePtr)malloc(sizeof(Node));
        ret->prior = rand();
        ret->size = 1;
        ret->val = val;
        ret->sum = val;
        ret->lazy = 0;
        ret->l = ret->r = NULL;
        return ret;
    }

    int range_query(NodePtr t, int l, int r) { // [l,r]
        NodePtr L, mid, R;
        split(t, L, mid, l-1);
        split(mid, t, R, r-l);
        int ans = t->sum;
        merge(mid, L, t);
        merge(t, mid, R);
        return ans;
    }

    void range_update(NodePtr t, int l, int r, int val) { // [l,r]
        NodePtr L, mid, R;
        split(t, L, mid, l-1);
        split(mid, t, R, r-l);
        t->lazy += val;
        merge(mid, L, t);
        merge(t, mid, R);
    }

    NodePtr build_treap(const vector<int>& a, int i, int j) {
        // [i, j)
        if (i == j-1) {
            return ImplicitTreap::init(a[i]);
        }
        int mid = (i+j)/2;
        Node* left = build_treap(a, i, mid);
        Node* right = build_treap(a, mid, j);
        Node* ret;
        ImplicitTreap::merge(ret, left, right);
        return ret;
    }

    NodePtr build_treap(const vector<int>& a) {
        return build_treap(a, 0, a.size());
    }
};


// 1-indexed, 0 means null
class ImplicitTreap2 {
    struct Node {
        int prior, size;
        int val;  // value stored in the array
        int sum;  // whatever info you want to maintain in segtree for the node
        int lazy; // whatever lazy update you want to do
        int l, r;
    };
public:
    ImplicitTreap2(int cap): cap_(cap) {
        alloc();
    }

    ~ImplicitTreap2() {
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
    void combine(int& t, int l, int r) {
        // TODO: can we remove this check?
        if (!l || !r) {
            t = (l ? l : r);
            return;
        }
        nodes_[t].sum = nodes_[l].sum + nodes_[r].sum;
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
        combine(t, node.l, t);
        combine(t, t, node.r);
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
