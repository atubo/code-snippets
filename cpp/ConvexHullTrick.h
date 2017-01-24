
namespace ConvextHullTrick {

    const int MAXN = 50010;
    int64_t C[MAXN];
    int64_t S[MAXN];
    int64_t dp[MAXN];
    int N;

    int64_t Y(int i) {
        // implementation
        return 0;
    }

    int64_t X(int i) {
        // implementation
        return 0;
    }

    int64_t numer(int k, int j) {
        return Y(j) - Y(k);
    }

    int64_t denom(int k, int j) {
        return X(j) - X(k);
    }

    bool isConvex(int a, int b, int c) {
        return numer(a, b) * denom(b, c) <= numer(b, c) * denom(a, b);
    }

    int64_t getDp(int i, int j) {
        // implementation
        return 0;
    }

    void runDp() {
        // initialize N and S

        dp[0] = 0;
        deque<int> q;
        q.push_back(0);
        for (int i = 1; i <= N; i++) {
            while (q.size() > 1 && numer(q[0], q[1]) <= denom(q[0], q[1]) * S[i]) {
                q.pop_front();
            }
            dp[i] = getDp(i, q.front());
            while (q.size() > 1 && !isConvex(q[q.size()-2], q[q.size()-1], i)) {
                q.pop_back();
            }
            q.push_back(i);
        }
    }
}
