// convert non-coprime moduli to coprime moduli
// so we can use Chinese remainder

class ChineseRemainderPreprocessor {
    struct Factor {
        int64_t prime;
        int power;
    };

    struct EquationInPrimePower {
        int power;
        int64_t r;
    };

    struct Equation {
        int64_t r;
        int64_t modulus;
    };

public:
    ChineseRemainderPreprocessor(int n): n_(n), m_(n_) {
        alloc();
    }

    ~ChineseRemainderPreprocessor() {
        dealloc();
    }

    void setRemainder(int i, int64_t a) {
        a_[i] = a;
    }

    void addModFactor(int i, int64_t p, int n) {
        m_[i].push_back({p, n});
        sorted_primes_.push_back(p);
    }

    bool process() {
        sort(sorted_primes_.begin(), sorted_primes_.end());
        sorted_primes_.erase(unique(sorted_primes_.begin(),
                                    sorted_primes_.end()),
                             sorted_primes_.end());

        vector<EquationInPrimePower> equations(sorted_primes_.size(),
                                               {-1, 0});
        for (int i = 0; i < n_; i++) {
            int64_t r = a_[i];
            for (const auto &f: m_[i]) {
                int64_t p = f.prime;
                int n = f.power;
                int pidx = lower_bound(sorted_primes_.begin(),
                                       sorted_primes_.end(),
                                       p) - sorted_primes_.begin();
                if (equations[pidx].power == -1) {
                    equations[pidx] = {n, r % qpow(p, n)};
                    continue;
                }
                if (n >= equations[pidx].power) {
                    if (r % qpow(p, equations[pidx].power) !=
                        equations[pidx].r) {
                        return false;
                    }
                    equations[pidx] = {n, r % qpow(p, n)};
                } else {
                    if (equations[pidx].r % qpow(p, n) != r % qpow(p, n)) {
                        return false;
                    }
                }
            }
        }
        for (int i = 0; i < (int)sorted_primes_.size(); i++) {
            auto &eq = equations[i];
            equ.push_back({eq.r, qpow(sorted_primes_[i], eq.power)});
        }
        return true;
    }

    vector<Equation> equ;
private:
    const int n_;
    int64_t *a_;
    vector<vector<Factor>> m_;
    vector<int64_t> sorted_primes_;

    void alloc() {
        a_ = new int64_t[n_]{};
    }

    void dealloc() {
        delete[] a_;
    }

    static int64_t qpow(int64_t x, int n) {
        int64_t ret = 1;
        while (n) {
            if (n & 1) ret *= x;
            x *= x;
            n >>= 1;
        }
        return ret;
    }
};
