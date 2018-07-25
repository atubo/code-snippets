
namespace ConvextHullTrick {

    const int MAXN = 50010;
    int64_t C[MAXN];    // save input array here
    int64_t S[MAXN];
    int64_t dp[MAXN];
    int buf[MAXN];
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
        return numer(a, b) * denom(b, c) < numer(b, c) * denom(a, b);
    }

    int64_t getDp(int i, int j) {
        // implementation
        return 0;
    }

    void runDp() {
        // initialize N and S

        dp[0] = 0;
        int p = 0, q = 0;
        buf[q++] = 0;
        for (int i = 1; i <= N; i++) {
            // it may make sense to skip 0 elements
            // if that's the case, un-comment the following
            /*
            if (S[i] == S[i-1]) {
                dp[i] = dp[i-1];
                continue;
            }
            */
            while (q-p > 1 &&
                   numer(buf[p], buf[p+1]) <= denom(buf[p], buf[p+1]) * S[i]) {
                p++;
            }
            dp[i] = getDp(i, buf[p]);
            while (q-p > 1 && !isConvex(buf[q-2], buf[q-1], i)) {
                q--;
            }
            buf[q++] = i;
        }
    }
}
