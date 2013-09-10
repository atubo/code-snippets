
// Get the next permuation of bitmask x
int permutate(int x)
{
    int k = 0;
    while ((x >> k & 0x1) == 0) k++;
    int j = k;
    while (((x >> j & 0x1) == 1) && j < 32) j++;
    if (j == 32) return -1;
    --j;
    x |= 1 << (j+1);
    x &= ~(1 << k);
    x &= ~((1 << j+1) - 1);
    x |= (1 << j - k) - 1;
    return x;
}

