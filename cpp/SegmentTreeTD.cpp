#include <limits>
#include <inttypes.h>

using namespace std;

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
            M[node].update(M[2*node], M[2*node+1]);
        }
    }

    typename D::QVType query(int i, int j) const {
        return query(1, 0, N-1, i, j, typename D::Query());
    }

	void update(int i, int j,
                const typename D::UVType& d) {
		update(1, 0, N-1, i, j, typename D::Updator(d));
	}

private:
	int N;
	D* M;

    typename D::QVType query(int node, int b, int e, int i, int j,
                             typename D::Query q) const {
        if (i > e || j < b) {
            return D::Query::nullValue();
        }

        q.update(M[node]);
        if (b >= i && e <= j) {
            return q.getValue(M[node]);
        }

        typename D::QVType p1 = query(2*node, b, (b+e)/2, i, j, q);
        typename D::QVType p2 = query(2*node+1, (b+e)/2+1, e, i, j, q);

        return q.combineValues(p1, p2);
    }

    void update(int node, int b, int e, int i, int j,
                typename D::Updator const & u) {
        if (i > e || j < b) {
            return;
        }
        if (b >= i && e <= j) {
            u.updateNode(M[node]);
            return;
        }
        update(2*node, b, (b+e)/2, i, j, u);
        update(2*node+1, (b+e)/2+1, e, i, j, u);
        M[node].update(M[2*node], M[2*node+1]);
    }
};
