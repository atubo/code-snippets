
class SparseTableRMQ {
public:
    int N, MAXB;
    vector<int> A;
    vector<vector<int> > st;

public:
    SparseTableRMQ() {
        // initialize N, A
    }

    void preCompute() {
        MAXB = 0;
        int x = 1;
        while (x <= N) {
            MAXB++;
            x = x * 2;
        }

        st.resize(N);
        for (int i = 0; i < N; i++) {
            st[i].resize(MAXB, INT_MAX);
            st[i][0] = A[i];
        }

        for (int j = 1; j < MAXB; j++) {
            for (int i = 0; i + (1 << j) - 1 < N; i++) {
                st[i][j] = min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
            }
        }
    }

    int rmq(int u, int v) {
        int j = 0;
        while (u + (1 << (j+1)) < v+1) j++;
        return min(st[u][j], st[v+1-(1<<j)][j]);
    }
};
