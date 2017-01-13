## Suffix Array
Usage:
Let $s(x)$ be the suffix starting at position $x$ and $S_{i, j}$ be the substring of $S$ from $i$ to $j$.
* To build the suffix array
```c++
SuffixArray::S = s;
SuffixArray::buildSA();
SuffixArray::buildLCP();
```
* `calcLCP(x, y)` returns the length of the longest common prefix of $s(x)$ and $s(y)$.
* `sa[x]`: the index of $s(x)$ in the suffix array.
* `pos[i]`: the starting position of `i`th suffix in the suffix array.
* `P[k][i]`: the rank of $S_{i,i+2^k}$
