#include <functional>
#include <limits>
#include <inttypes.h>

using namespace std;

/*
 This data structure supports
 1. Range query
 2. Range update

 Requirements:
 1. range update can be characterized by a parameter d
 2. range update should be commutative and associative
 3. we can accumulate the updates, i.e. U(d1)U(d2)...=U(d1+d2+..)
 4. A(U(x1, x2, .. , d)) = U'(A(x1, x2, ..), d, |x1, x2,..|)

 Client should provide three lambdas:
 1. combine (get aggregate from elements)
 2. accumulate (accumulate update parameters)
 3. apply (apply the update, may depend on set size)

 Template parameters (usually they are the same type):
 V - value type
 D - parameter type
*/
template<typename V, typename D=V>
class SegmentTreeTD {
    struct Node {
        Node(): value(0), update(0),count(0) {}
        V value;
        D update;
        int count;
    };

public:
    SegmentTreeTD(int N_, V A[], V zero_,
                  function<V(V, V)> combine_,
                  function<D(D, D)> accu_,
                  function<V(V, D, int)> apply_):
        N(N_), zero(zero_), combine(combine_), accu(accu_), apply(apply_) {
        int nlog = 0;
        int n = N;
        while (n > 0) {
            n = (n >> 1);
            nlog++;
        }
        int msize = 2 * (1 << (nlog+1)) + 1;
        M = new Node[msize];
        initialize(1, 0, N-1, A);
    }

    ~SegmentTreeTD() {
        delete[] M;
    }

    void initialize(int node, int b, int e, V A[]) {
        if (b == e) {
            M[node].value = A[b];
            M[node].count = 1;
        }
        else {
            initialize(2*node, b, (b+e)/2, A);
            initialize(2*node+1, (b+e)/2+1, e, A);
            M[node].value = combine(eval(M[2*node]), eval(M[2*node+1]));
            M[node].count = M[2*node].count + M[2*node+1].count;
        }
    }

    // i, j inclusive
    V query(int i, int j) const {
        return query(1, 0, N-1, i, j, D(0));
    }

    void update(int i, int j, D d) {
        update(1, 0, N-1, i, j, d);
    }

private:
    const int N;
    const V zero;   // zero element for combine

    function<V(V, V)> combine;
    function<D(D, D)> accu;
    function<V(V, D, int)> apply;

    Node* M;

    V eval(const Node& node) const {
        return apply(node.value, node.update, node.count);
    }

    V eval(const Node& node, D d, int count) const {
        return apply(node.value, d, count);
    }

    V query(int node, int b, int e, int i, int j, D d) const {
        if (i > e || j < b) {
            return zero;
        }

        d = accu(d, M[node].update);
        if (b >= i && e <= j) {
            return eval(M[node], d, e-b+1);
        }

        V p1 = query(2*node, b, (b+e)/2, i, j, d);
        V p2 = query(2*node+1, (b+e)/2+1, e, i, j, d);

        return combine(p1, p2);
    }

    void update(int node, int b, int e, int i, int j, D d) {
        if (i > e || j < b) {
            return;
        }
        if (b >= i && e <= j) {
            M[node].update = accu(M[node].update, d);
            return;
        }
        update(2*node, b, (b+e)/2, i, j, d);
        update(2*node+1, (b+e)/2+1, e, i, j, d);
        M[node].value = combine(eval(M[2*node]), eval(M[2*node+1]));
    }
};
