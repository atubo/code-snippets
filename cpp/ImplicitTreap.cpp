// https://threads-iiith.quora.com/Treaps-One-Tree-to-Rule-em-all-Part-2
#include <stddef.h>
#include <stdlib.h>

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
};

