
class LIS {
public:
    static int solve(const vector<int>& A) {
        const int N = A.size();
        vector<int> C(N+1, INT_MAX);
        C[0] = 0;
        int ret = 0;
        for (int x: A) {
            int p = lower_bound(C.begin(), C.end(), x) - C.begin();
            ret = max(ret, p);
            C[p] = min(C[p], x);
        }
        return ret;
    }
};
