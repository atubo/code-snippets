// square matrix fast power
class Matrix {
public:
    int **_m;
    int _n;

public:
    Matrix(int n): _n(n) {
        alloc();
    }

    Matrix(const Matrix &other) {
        _n = other._n;
        alloc();
        for (int i = 0; i < _n; i++) {
            memcpy(_m[i], other._m[i], _n * sizeof(int));
        }
    }


    ~Matrix() {
        for (int i = 0; i < _n; i++) {
            delete[] _m[i];
        }
        delete[] _m;
    }

    void alloc() {
        _m = new int*[_n]{};
        for (int i = 0; i < _n; i++) {
            _m[i] = new int[_n]{};
        }
    }


#if 0
    Matrix& operator *= (const Matrix &rhs) {
        Matrix ret(_n);
        for (int i = 0; i < _n; i++) {
            for (int j = 0; j < _n; j++) {
                for (int k = 0; k < _n; k++) {
                    ret._m[i][j] += (_m[i][k] * rhs._m[k][j]) % MOD;
                    ret._m[i][j] %= MOD;
                }
            }
        }
        swap(ret);
        return *this;
    }
#endif

    void mul(const Matrix &rhs, Matrix &tmp) {
        for (int i = 0; i < _n; i++) {
            memset(tmp._m[i], 0, _n * sizeof(int));
            for (int k = 0; k < _n; k++) {
                if (!_m[i][k]) continue;
                for (int j = 0; j < _n; j++) {
                    tmp._m[i][j] += _m[i][k] * rhs._m[k][j];
                }
            }
        }
        swap(tmp);
    }

    void swap(Matrix &other) {
        std::swap(_m, other._m);
    }

    static Matrix power(Matrix x, int n) {
        Matrix ret(x._n), tmp(x._n);
        for (int i = 0; i < x._n; i++) ret._m[i][i] = 1;
        while (n) {
            if (n & 1) ret.mul(x, tmp);
            x.mul(x, tmp);
            n >>= 1;
        }
        return ret;
    }

    void print() const {
        for (int i = 0; i < _n; i++) {
            for (int j = 0; j < _n; j++) {
                printf("%d ", _m[i][j]);
            }
            printf("\n");
        }
    }
};
