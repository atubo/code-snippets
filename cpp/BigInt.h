
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
        string a(A), b(B);
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());

        if (a.length() > b.length()) swap(a, b);

        string ret;
        int carry = 0;
        for (int i = 0; i < (int)b.length(); i++) {
            int d = (i < (int)a.length() ? a[i] - '0' : 0) + b[i] - '0' + carry;
            ret.push_back('0' + (d%10));
            carry = d/10;
        }

        if (carry) {
            ret.push_back('1');
        }

        reverse(ret.begin(), ret.end());
        return ret;
    }

    static string sub(const string& A, const string& B) {
        assert(less(B, A) || A == B);
        string a = A;
        string b = B;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());

        string ret;
        int borrow = 0;
        for (int i = 0; i < (int)a.length(); i++) {
            int d = a[i] - '0' - (i < (int)b.length() ? b[i] - '0' : 0) - borrow;
            if (d < 0) {
                d += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            ret.push_back(d + '0');
        }
        assert(borrow == 0);
        // remove trailing zeros before reversing
        for (int i = (int)ret.size()-1; i > 0; i--) {
            if (ret[i] != '0') break;
            ret.erase(i);
        }

        reverse(ret.begin(), ret.end());
        return ret;
    }
};
