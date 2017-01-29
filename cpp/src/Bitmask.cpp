
// Get the next permuation of bitmask x
// return -1 when there is no next permutation
int permutate(int x, int N=32)
{
    int k = 0;
    while ((x >> k & 0x1) == 0) k++;
    int j = k;
    while (((x >> j & 0x1) == 1) && j < N) j++;
    if (j == N) return -1;
    --j;
    x |= 1 << (j+1);
    x &= ~(1 << k);
    x &= ~((1 << (j+1)) - 1);
    x |= (1 << (j - k)) - 1;
    return x;
}

