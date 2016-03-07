#include <cinttypes>

int64_t xorUpto(int64_t n)
{
    // 2n xor (2n+1) has only the last digit 1
    if (n == 0) return 0;
    int64_t x = ((n+1)/2) % 2;
    if (n % 2 == 0) x = n | x;
    return x;
}
