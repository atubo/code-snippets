// UnionFind with rollback
// All operations to be rolled-back must be together
// and after all committed operations.
// All tentative operations are built on top of
// the committed operations, i.e. its nodes are
// the group leads of the underlying UF

// Here we use only path compression, not union by rank
// for the simplicity of the implementation

class UnionFindRB {
private:
    const int N;
    vector<int> parentTentative;
    vector<int> parentCommitted;

    vector<bool> mark;
    vector<int> cg; // nodes to be reset

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parentTentative[k] = k;
        parentCommitted[k] = k;
    }

    void linkCommitted(int u, int v) {
        parentCommitted[u] = v;
    }

    void linkTentative(int u, int v) {
        parentTentative[u] = v;
    }

public:
    UnionFindRB(int n): N(n) {
        parentTentative.resize(N);
        parentCommitted.resize(N);

        mark.resize(N);
        cg.reserve(N);

        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    int findCommitted(int k) {
        if (parentCommitted[k] == k) return k;
        int root = findCommitted(parentCommitted[k]);
        return parentCommitted[k] = root;
    }

    int findTentative(int k) {
        if (parentTentative[k] == k) return k;
        int root = findTentative(parentTentative[k]);
        return parentTentative[k] = root;
    }

    int find(int k) {
        k = findCommitted(k);
        return findTentative(k);
    }

    void joinCommit(int u, int v) {
        u = findCommitted(u);
        v = findCommitted(v);
        if (u != v) {
            linkCommitted(u, v);
        }
    }

    void joinTentative(int u, int v) {
        u = findCommitted(u);
        v = findCommitted(v);
        if (!mark[u]) {
            mark[u] = true;
            cg.push_back(u);
        }
        if (!mark[v]) {
            mark[v] = true;
            cg.push_back(v);
        }

        u = findTentative(u);
        v = findTentative(v);
        if (u != v) {
            linkTentative(u, v);
        }
    }

    void rollback() {
        for (int i = (int)cg.size()-1; i >= 0; i--) {
            int u = cg[i];
            mark[u] = false;
            parentTentative[u] = u;
        }
    }

    void resetCommitted() {
        for (int i = 0; i < N; i++) {
            parentCommitted[i] = i;
        }
    }
};
