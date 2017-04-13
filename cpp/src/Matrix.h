// square matrix fast power
class Matrix {
public:
    vector<vector<int>> _m;
    int _n;

public:
    Matrix(int n): _n(n) {
        _m.resize(n);
        for (int i = 0; i < n; i++) {
            _m[i].resize(n);
        }
    }

    Matrix& operator *= (const Matrix &rhs) {
        Matrix ret(_n);
        for (int i = 0; i < _n; i++) {
            for (int j = 0; j < _n; j++) {
                for (int k = 0; k < _n; k++) {
                    ret._m[i][j] += _m[i][k] * rhs._m[k][j];
                }
            }
        }
        swap(ret);
        return *this;
    }

    void swap(Matrix &other) {
        _m.swap(other._m);
    }

    static Matrix power(const Matrix &x, int n) {
        if (n == 1) return x;
        Matrix y = power(x, n/2);
        y *= y;
        if (n & 1) y *= x;
        return y;
    }

    void print() const {
        for (int i = 0; i < _n; i++) {
            for (int x: _m[i]) {
                printf("%d ", x);
            }
            printf("\n");
        }
    }
};
