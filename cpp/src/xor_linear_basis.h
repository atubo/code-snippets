
class XorLinearBasis {
public:
    int64_t *a;

    XorLinearBasis(int maxl): maxl_(maxl) {
        alloc();
    }

    XorLinearBasis(const XorLinearBasis &b) {
        maxl_ = b.maxl_;
        alloc();
        memcpy(a, b.a, maxl_*sizeof(int64_t));
    }

    ~XorLinearBasis() {
        delete[] a;
    }

    void insert(int64_t t) {
        for (int j = maxl_; j >= 0; j--) {
            if (!(t & (1ll << j))) continue;

            if (a[j]) t ^= a[j];
            else {
                for (int k = 0; k < j; k++) {
                    if (t & (1ll << k)) t ^= a[k];
                }

                for (int k = j+1; k <= maxl_; k++) {
                    if (a[k] & (1ll << j)) a[k] ^= t;
                }
                a[j] = t;
                return;
            }
        }
    }

    void mergeFrom(const XorLinearBasis &other) {
        for (int i = 0; i <= maxl_; i++) {
            insert(other.a[i]);
        }
    }

    static XorLinearBasis merge(const XorLinearBasis &a,
                                const XorLinearBasis &b) {
        XorLinearBasis res = a;
        for (int i = 0; i <= res.maxl_; i++) {
            res.insert(b.a[i]);
        }
        return res;
    }

private:
    int maxl_;

    void alloc() {
        a = new int64_t[maxl_+1]{};
    }
};
