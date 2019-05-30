class PersistentBinaryTrie {
public:
    struct Node {
        int children[2];
        int count;
        Node() {
            children[0] = children[1] = 0;
            count = 0;
        }
    };

    PersistentBinaryTrie(int n, int nd): n_(n), nd_(nd) {
        root_ = new int[n_+1]{};
        nodes_ = new Node[(n_+1) * (nd_+1)]{};
    }

    ~PersistentBinaryTrie() {
        delete[] root_;
        delete[] nodes_;
    }

    void insert(int currRootIndex, int prevRootIndex, int x) {
        root_[currRootIndex] = root_[prevRootIndex];
        doInsert(root_[currRootIndex], x, nd_);
    }

    int query(int rootIndex, int x) const {
        Node node = nodes_[root_[rootIndex]];
        for (int i = nd_-1; i >= 0; i--) {
            int d = (x >> i) & 1;
            int c = node.children[d];
            if (c == 0) return 0;
            node = nodes_[c];
        }
        return node.count;
    }

    void print(int id) const {
        if (id == 0) return;
        printf("node=%d left=%d right=%d count=%d\n",
               id, nodes_[id].children[0], nodes_[id].children[1],
               nodes_[id].count);
        print(nodes_[id].children[0]);
        print(nodes_[id].children[1]);
    }

private:
    int n_; // number of positions, index is 1-based
    int nd_;    // number of digits
    int *root_;
    Node *nodes_;
    int currIdx_ = 1;

    void doInsert(int &now, int x, int d) {
        nodes_[currIdx_++] = nodes_[now];
        now = currIdx_ - 1;
        nodes_[now].count++;
        if (d == 0) return;
        d--;
        int t = (x >> d) & 1;
        doInsert(nodes_[now].children[t], x, d);
    }
};
