public class UnionFind {
    private final int N;
    private int[] rank;
    private int[] parent;

    public UnionFind(int n) {
        N = n;
        rank   = new int[n];
        parent = new int[n];

        for (int i = 0; i < n; i++) {
            makeSet(i);
        }
    }

    private void makeSet(int k) {
        assert 0 <= k && k < N;

        parent[k] = k;
        rank[k]   = 0;
    }

    public int find(int k) {
        if (parent[k] != k) {
            parent[k] = find(parent[k]);
        }
        return parent[k];
    }

    private void link(int u, int v) {
        if (rank[u] > rank[v]) {
            parent[v] = u;
        } else {
            parent[u] = v;
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
        }
    }

    public void join(int u, int v) {
        link(find(u), find(v));
    }
}
