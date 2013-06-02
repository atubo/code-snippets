#include <limits>
#include <inttypes.h>

using namespace std;

typedef int64_t ll;

template<class D>
class SegmentTreeTD {
public:
	SegmentTreeTD(int N_, D A[]): N(N_) {
		int nlog = 0;
		int n = N;
		while (n > 0) {
			n = (n >> 1);
			nlog++;
		}
		int msize = 2 * (1 << (nlog+1)) + 1;
		M = new D[msize];
		initialize(1, 0, N-1, A);
	}

	~SegmentTreeTD() {
		delete[] M;
	}

	void initialize(int node, int b, int e, D A[]) {
		if (b == e) {
			M[node] = A[b];
		}
		else {
			initialize(2*node, b, (b+e)/2, A);
			initialize(2*node+1, (b+e)/2+1, e, A);
			//M[node].val = min(M[2*node].val, M[2*node+1].val);
            M[node].update(M[2*node], M[2*node+1]);
		}
	}

    template<class Q>
	ll query(int i, int j, Q q) const {
		return query(1, 0, N-1, i, j, q);
	}

    template<class U>
	void update(int i, int j, const U& u) {
		update(1, 0, N-1, i, j, u);
	}

private:
	int N;
	D* M;

    template<class Q>
	ll query(int node, int b, int e, int i, int j, Q q) const {
		if (i > e || j < b) {
			//return MAXINT;
            return Q::nullValue();
		}

		//acc += M[node].delta;
        q.update(M[node]);
		if (b >= i && e <= j) {
			//return M[node].val + acc;
            return q.getValue(M[node]);
		}

		ll p1 = query(2*node, b, (b+e)/2, i, j, q);
		ll p2 = query(2*node+1, (b+e)/2+1, e, i, j, q);

		//return min(p1, p2);
        return q.combineValues(p1, p2);
	}

    template<class U>
	void update(int node, int b, int e, int i, int j, const U& u) {
		if (i > e || j < b) {
			return;
		}
		if (b >= i && e <= j) {
			//M[node].delta += d;
            u.updateNode(M[node]);
			return;
		}
		update(2*node, b, (b+e)/2, i, j, u);
		update(2*node+1, (b+e)/2+1, e, i, j, u);
		//M[node].val = min(M[2*node].delta + M[2*node].val,
		//				  M[2*node+1].delta + M[2*node+1].val);
        M[node].update(M[2*node], M[2*node+1]);
	}
};
