
class Ntt {
public:
    static int primeRoot(int p) {
        vector<int> factors;
        int x = p - 1;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                factors.push_back((p-1)/i);
                while (x % i == 0) x /= i;
            }
        }
        if (x > 1) factors.push_back(x);

        for (int i = 2; ; i++) {
            bool ok = true;
            for (int y: factors) {
                if (pow(i, y, p) == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) return i;
        }
        return -1;
    }

    static void ntt(vector<int> &a, int op, int p, int g) {
        // length should be power of 2
        const int n = a.size();
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (j > i) {
                swap(a[i], a[j]);
            }
            int m = (n >> 1);
            while (m >= 2 && j >= m) {
                j -= m;
                m >>= 1;
            }
            j += m;
        }

        for (int i = 1; i < n; i<<=1) {
            int64_t wn = pow(g, op==1?(p-1)/(2*i):p-1-(p-1)/(2*i), p), t, w;
            for (j = 0; j < n; j+=i<<1) {
                w = 1;
                for (int k = 0; k < i; k++) {
                    t = w*a[i+j+k]%p; w = w*wn%p;
                    a[i+j+k] = (a[j+k]-t+p)%p;
                    a[j+k] = (a[j+k]+t)%p;
                }
            }
        }

        if (op == -1) {
            int64_t inv = pow(n, p-2, p);
            for (int i = 0; i < n; i++) a[i] = a[i] * inv % p;
        }
    }

    static vector<int> innerProduct(const vector<int> &a, const vector<int>& b,
                                    int p) {
        const int n = a.size();
        vector<int> c(n);
        for (int i = 0; i < n; i++) {
            c[i] = int64_t(a[i]) * b[i] % p;
        }
        return c;
    }

    static vector<int> conv(vector<int> a, vector<int> b,
                            int p, int g) {
        ntt(a, 1, p, g);
        ntt(b, 1, p, g);
        vector<int> c = innerProduct(a, b, p);
        ntt(c, -1, p, g);
        return c;
    }
        
private:
    static int pow(int64_t x, int y, int m) {
        int64_t ans = 1;
        while (y) {
            if (y & 1) ans = ans * x % m;
            x = x * x % m;
            y >>= 1;
        }
        return ans;
    }
};
