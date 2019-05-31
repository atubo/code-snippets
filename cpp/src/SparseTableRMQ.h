class SparseTableRMQ {
public:
    SparseTableRMQ(int *a, int n): n_(n), maxb_(log2(n)+1.5) {
        alloc();
        preCompute(a);
    }

    ~SparseTableRMQ() {
        dealloc();
    }

    // RMQ for range [u, v]
    int rmq(int u, int v) const {
        int j = log_[v-u+1];
        return max(st_[u][j], st_[v+1-(1<<j)][j]);
    }
private:
    int n_;
    int maxb_;
    int **st_;
    int *log_;

    void alloc() {
        st_ = new int*[n_]{};
        for (int i = 0; i < n_; i++) {
            st_[i] = new int[maxb_]{};
            for (int j = 0; j < maxb_; j++) {
                st_[i][j] = INT_MIN;
            }
        }
        log_ = new int[n_+1]{};
    }

    void dealloc() {
        delete[] log_;
        for (int i = 0; i < n_; i++) {
            delete[] st_[i];
        }
        delete[] st_;
    }

    void preCompute(int *a) {
        for (int i = 2; i <= n_; i++) log_[i] = log_[i>>1] + 1;

        for (int i = 0; i < n_; i++) {
            st_[i][0] = a[i];
        }

        for (int j = 1; j < maxb_; j++) {
            for (int i = 0; i + (1 << j) - 1 < n_; i++) {
                st_[i][j] = max(st_[i][j-1], st_[i+(1<<(j-1))][j-1]);
            }
        }
    }

};
