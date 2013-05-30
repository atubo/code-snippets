#include <limits>
#include <inttypes.h>

using namespace std;

typedef int64_t ll;

const ll MAXINT = numeric_limits<ll>::max();

struct Node {
	Node(): delta(0), val(MAXINT) {}
	ll delta;
	ll val;
};

class SegmentTreeTD {
public:
	SegmentTreeTD(int N_, ll A[]): N(N_) {
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

	void initialize(int node, int b, int e, ll A[]) {
		if (b == e) {
			M[node].val = A[b];
		}
		else {
			initialize(2*node, b, (b+e)/2, A);
			initialize(2*node+1, (b+e)/2+1, e, A);
			M[node].val = min(M[2*node].val, M[2*node+1].val);
		}
	}

	ll query(int i, int j) const {
		return query(1, 0, N-1, i, j, 0);
	}

	void update(int i, int j, ll d) {
		update(1, 0, N-1, i, j, d);
	}

private:
	int N;
	Node* M;

	ll query(int node, int b, int e, int i, int j, ll acc) const {
		if (i > e || j < b) {
			return MAXINT;
		}

		acc += M[node].delta;
		if (b >= i && e <= j) {
			return M[node].val + acc;
		}

		ll p1 = query(2*node, b, (b+e)/2, i, j, acc);
		ll p2 = query(2*node+1, (b+e)/2+1, e, i, j, acc);

		return min(p1, p2);
	}

	void update(int node, int b, int e, int i, int j, ll d) {
		if (i > e || j < b) {
			return;
		}
		if (b >= i && e <= j) {
			M[node].delta += d;
			return;
		}
		update(2*node, b, (b+e)/2, i, j, d);
		update(2*node+1, (b+e)/2+1, e, i, j, d);
		M[node].val = min(M[2*node].delta + M[2*node].val,
						  M[2*node+1].delta + M[2*node+1].val);
	}
};
