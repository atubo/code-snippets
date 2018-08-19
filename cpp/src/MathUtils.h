// 1 ^ 2 ^ 3 ^ ... ^ n
int64_t xorUpto(int64_t n)
{
    // 2n xor (2n+1) has only the last digit 1
    if (n == 0) return 0;
    int64_t x = ((n+1)/2) % 2;
    if (n % 2 == 0) x = n | x;
    return x;
}


int64_t countOnesRecur(int64_t n, int64_t factor)
{
    if (n <= 0) return 0;
    // count 1's on the LSD
    int64_t result = (n+1)/2;
    // count 1's in n downto its nearest even neighbor
    int64_t ntmp = (n >> 1);
    while (ntmp > 0) {
        result += (ntmp & 1) * ((n&1) + 1);
        ntmp = (ntmp >> 1);
    }

    return result * factor + countOnesRecur((n>>1)-1, factor<<1);
}

// count number of 1's in the binary representations
// of all numbers from 1 up to n
int64_t countOnes(int64_t n)
{
    return countOnesRecur(n, 1);
}

// generate binomial coefficients
// binom[n][k] = n \choose k
namespace Binom {
    const int MAXN = 1005;
    int binom[MAXN][MAXN];

    void generate(int N) {
        binom[0][0] = 1;
        for (int i = 1; i <= N; i++) {
            binom[i][0] = 1;
            for (int j = 1; j <= i; j++) {
                binom[i][j] = binom[i-1][j] + binom[i-1][j-1];
            }
        }
    }
}

int64_t phi(int64_t a) {
    int64_t ans = 1;
    for (int64_t p = 2; p * p <= a; p++) {
        if (a % p == 0) {
            ans *= (p-1);
            a /= p;
            while (a % p == 0) {
                a /= p;
                ans *= p;
            }
        }
    }
    if (a > 1) ans *= (a-1);
    return ans;
}

