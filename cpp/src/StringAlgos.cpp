#include <cinttypes>
#include <string>

using namespace std;

int64_t numCommonSubsequences(const string& s1, const string& s2)
{
    const int N = s1.length();
    const int M = s2.length();
    int64_t dp[N+1][M+1];
    for (int i = 0; i < M+1; i++) dp[0][i] = 0;
    for (int i = 0; i < N+1; i++) dp[i][0] = 0;

    for (int i = 1; i < N+1; i++) {
        for (int j = 1; j < M+1; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i][j-1] + dp[i-1][j] + 1;
            } else {
                dp[i][j] = dp[i][j-1] + dp[i-1][j] - dp[i-1][j-1];
            }
        }
    }
    return dp[N][M];
}
