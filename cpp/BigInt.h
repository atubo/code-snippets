
class BigInt {
public:
    static string mod(const string& A, const string& B) {
        vector<string> dbls;
        dbls.push_back(B);
        while (less(dbls.back(), A)) {
            dbls.push_back(add(dbls.back(), dbls.back()));
        }
        string a = A;
        for (int i = (int)dbls.size()-1; i >= 0; i--) {
            if (less(a, dbls[i])) continue;
            a = sub(a, dbls[i]);
        }
        return a;
    }

    static bool less(const string& a, const string& b) {
        // check if a < b
        return (a.length() < b.length() ||
                (a.length() == b.length() && a < b));
    }

    static string add(const string& A, const string& B) {
        const int N = A.length();
        const int M = B.length();

        const int L = max(N, M);
        string ret(L, char());
        int carry = 0;
        for (int i = 0; i < L; i++) {
            int d = (i < N ? A[N-1-i] - '0' : 0) + (i < M ? B[M-1-i] - '0' : 0) + carry;
            ret[L-1-i] = '0' + (d%10);
            carry = d/10;
        }

        if (carry) {
            ret.insert(0, 1, '1');
        }

        return ret;
    }

    static string sub(const string& A, const string& B) {
        assert(less(B, A) || A == B);
        const int N = A.length();
        const int M = B.length();

        string ret(N, char());
        int borrow = 0;
        for (int i = 0; i < N; i++) {
            int d = A[N-1-i] - '0' - (i < M ? B[M-1-i] - '0' : 0) - borrow;
            if (d < 0) {
                d += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            ret[N-1-i] = d + '0';
        }
        assert(borrow == 0);

        // remove leading zeros
        int p = 0;
        while (p < N-1 && ret[p] == '0') p++;
        if (p != 0) ret = ret.substr(p);
        return ret;
    }
};
