
class Rmq {
public:
    Rmq(int *a, int n): n_(n), maxb_(log2(n)+1) {
        alloc();
        preprocess(a);
    }

    ~Rmq() {
        dealloc();
    }

    int rmq(int u, int v) const {
        int j = log_[v-u+1];
        return max(st_[j][u], st_[j][v+1-(1<<j)]);
    }

private:
    int n_;
    int maxb_;
    int **st_;
    int *log_;

    void alloc() {
        st_ = new int*[maxb_]{};
        for (int i = 0; i < maxb_; i++) {
            st_[i] = new int[n_]{};
        }
        log_ = new int[n_]{};
    }

    void dealloc() {
        delete[] log_;
        for (int i = 0; i < maxb_; i++) {
            delete[] st_[i];
        }
        delete[] st_;
    }

    void preprocess(int *a) {
        for (int i = 2; i < n_; i++) log_[i] = log_[i>>1] + 1;

        for (int i = 0; i < n_; i++) {
            st_[0][i] = a[i];
        }

        for (int j = 1; j < maxb_; j++) {
            for (int i = 0; i + (1<<j) - 1 < n_; i++) {
                st_[j][i] = max(st_[j-1][i], st_[j-1][i+(1<<(j-1))]);
            }
        }
    }
};
