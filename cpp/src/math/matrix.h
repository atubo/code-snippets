// square matrix fast power
class Matrix {
public:
    int **m_;
    int n_;

public:
    Matrix(int n): n_(n) {
        alloc();
    }

    Matrix(const Matrix &other) {
        n_ = other.n_;
        alloc();
        for (int i = 0; i < n_; i++) {
            memcpy(m_[i], other.m_[i], n_ * sizeof(int));
        }
    }


    ~Matrix() {
        for (int i = 0; i < n_; i++) {
            delete[] m_[i];
        }
        delete[] m_;
    }

    void alloc() {
        m_ = new int*[n_]{};
        for (int i = 0; i < n_; i++) {
            m_[i] = new int[n_]{};
        }
    }


#if 0
    Matrix& operator *= (const Matrix &rhs) {
        Matrix ret(n_);
        for (int i = 0; i < n_; i++) {
            for (int j = 0; j < n_; j++) {
                for (int k = 0; k < n_; k++) {
                    ret.m_[i][j] += (m_[i][k] * rhs.m_[k][j]) % MOD;
                    ret.m_[i][j] %= MOD;
                }
            }
        }
        swap(ret);
        return *this;
    }
#endif

    void mul(const Matrix &rhs, Matrix &tmp) {
        for (int i = 0; i < n_; i++) {
            memset(tmp.m_[i], 0, n_ * sizeof(int));
            for (int k = 0; k < n_; k++) {
                if (!m_[i][k]) continue;
                for (int j = 0; j < n_; j++) {
                    tmp.m_[i][j] += m_[i][k] * rhs.m_[k][j];
                }
            }
        }
        swap(tmp);
    }

    void swap(Matrix &other) {
        std::swap(m_, other.m_);
    }

    static Matrix power(Matrix x, int n) {
        Matrix ret(x.n_), tmp(x.n_);
        for (int i = 0; i < x.n_; i++) ret.m_[i][i] = 1;
        while (n) {
            if (n & 1) ret.mul(x, tmp);
            x.mul(x, tmp);
            n >>= 1;
        }
        return ret;
    }

    void print() const {
        for (int i = 0; i < n_; i++) {
            for (int j = 0; j < n_; j++) {
                printf("%d ", m_[i][j]);
            }
            printf("\n");
        }
    }
};
