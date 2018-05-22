
class MultiTreeToBinaryTree {
    // nodes are 0-indexed
public:
    struct Node {
        Node(int l = -1, int r = -1): left(l), right(r) {}
        int left, right;

        bool operator == (const Node &other) const {
            return left == other.left && right == other.right;
        }
    };

    MultiTreeToBinaryTree(const vector<vector<int>> &children, int root)
        :children_(children) {
        n_ = children.size();
        alloc();
        build(root);
    }

    ~MultiTreeToBinaryTree() {
        dealloc();
    }

private:
    int n_;
    const vector<vector<int>> &children_;
public:
    Node *nodes;

private:
    void alloc() {
        nodes = new Node[n_]{};
    }

    void dealloc() {
        delete[] nodes;
    }

    void build(int r) {
        if (children_[r].empty()) return;
        int u = children_[r][0];
        build(u);
        nodes[r].left = u;
        for (int i = 1; i < (int)children_[r].size(); i++) {
            int v = children_[r][i];
            build(v);
            nodes[v].right = nodes[u].right;
            nodes[u].right = v;
        }
    }
};
