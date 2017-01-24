---
layout: post
title: C++ code documentation
---

## Suffix Array

### Code
[SuffixArray.h](https://github.com/atubo/code-snippets/blob/master/cpp/SuffixArray.h)

### Usage:
Let $s(x)$ be the suffix starting at position $x$ and $S_{i, j}$ be the substring of $S$ from $i$ to $j$.

* To build the suffix array

```cpp
SuffixArray::S = s;
SuffixArray::buildSA();
SuffixArray::buildLCP();
```

* `calcLCP(x, y)` returns the length of the longest common prefix of $s(x)$ and $s(y)$.
* `sa[i]`: the starting position of the `i`th suffix in the suffix array.
* `pos[x]`: the rank of $s(x)$ in the suffix array.
* `P[k][i]`: the rank of $S_{i,i+2^k}$

## 倍增LCA

### Code
[BinaryLiftLCA.h](https://github.com/atubo/code-snippets/blob/master/cpp/BinaryLiftLCA.h)

### Usage
```cpp
BinaryLiftLCA lca;  // initialize N, root and adj here
lca.preCompute();   // remember to do this!

// online computation of lca(u, v)
int x = lca.findLCA(u, v);
```

## Sparse table RMQ

### Code
[SparseTableRMQ.h](https://github.com/atubo/code-snippets/blob/master/cpp/SparseTableRMQ.h)

### Usage
```cpp
SparseTableRMQ rmq;   // initialize N and A
rmq.preCompute();     // remember to do this!

// online computation of RMQ
int x = rmq.rmq(a, b);
```
It calculates the minimum number in range $[a, b]$.

## Topological sort

### Code
[TopologicalSort.h](https://github.com/atubo/code-snippets/blob/master/cpp/TopologicalSort.h)

### Usage
```cpp
TopologicalSort t;  // initialize N and adj
t.sort(); // now t.topo has the sorted nodes
```
Let $\textrm{pos}(u)$ denote the position of node $u$ in ```t.topo``` array, for any edge $u \rightarrow v$, we have $\textrm{pos}(u)<\textrm{pos}(v)$.

## DP斜率优化模板

### Code
[ConvexHullTrick.h](https://github.com/atubo/code-snippets/blob/master/cpp/ConvexHullTrick.h)

### Usage
* $dp$ is 1-based, $dp[0]$ is the initial empty state.
* User needs to implement $Y()$, $X()$ and $\textrm{getDp}()$ functions.
* User needs to initialize N and S arrays
* Note that in $\textrm{numer}(k, j)$ and $\textrm{denom}(k, j)$, we need to have $k < j$.
The order matters because we need to keep $\textrm{denom}$ positive so that we can multiply the denominators when we
compare the fractions.
