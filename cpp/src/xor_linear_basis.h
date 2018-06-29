
class XorLinearBasis {
public:
    int64_t *a;

    XorLinearBasis(int maxl): maxl_(maxl) {
        a = new int64_t[maxl_+1]{};
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

private:
    int maxl_;
};
