namespace math {

class BinomModuloPrime {
    // n should be less than prime
private:
    const int n_;
    const int prime_;
    int *jc_;

public:
    BinomModuloPrime(int n, int prime): n_(n), prime_(prime) {
        alloc();
        init();
    }

    ~BinomModuloPrime() {
        dealloc();
    }

    int calc(int r) const {
        if (r > n_) return 0;
        int x1 = inverse(jc_[r]);
        int x2 = mul(jc_[n_], x1);
        int x3 = inverse(jc_[n_-r]);
        return mul(x2, x3);
    }

private:
    void alloc() {
        int sz = max(n_+1, 2);
        jc_ = new int[sz]{};
    }

    void dealloc() {
        delete[] jc_;
    }

    void init() {
        jc_[0] = jc_[1] = 1;
        for (int i = 2; i <= n_; i++) {
            jc_[i] = mul(jc_[i-1], i);
        }
    }

    int inverse(int x) const {
        return qpow(x, prime_-2);
    }

    int qpow(int x, int n) const {
        int ret = 1;
        while (n) {
            if (n & 1) ret = mul(ret, x);
            x = mul(x, x);
            n >>= 1;
        }
        return ret;
    }

    int mul(int64_t a, int64_t b) const {
        return (a * b) % prime_;
    }
};

class BinomLucas {
private:
    const int prime_;
public:
    BinomLucas(int prime): prime_(prime) {}

    int lucas(int64_t a, int64_t b) const {
        if (a < prime_ && b < prime_) return calc(a, b);
        return mul(calc(a % prime_, b % prime_),
                   lucas(a / prime_, b / prime_));
    }

    int calc(int a, int b) const {
        BinomModuloPrime binom(a, prime_);
        return binom.calc(b);
    }

private:
    int mul(int64_t a, int64_t b) const {
        return (a * b) % prime_;
    }
};

}
