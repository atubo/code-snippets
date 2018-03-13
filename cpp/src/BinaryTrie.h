
class BinaryTrie {
public:
    class Node {
    public:
        Node():children(2, NULL), count(0) {}

        ~Node() {
            for (Node* child: children) {
                delete child;
            }
        }

        vector<Node*> children;
        int count;
    };

    int N;
    Node* root;

    BinaryTrie(int N_): N(N_) {
        root = new Node();
    }

    ~BinaryTrie() {
        delete root;
    }

    void insert(int x) {
        Node* node = root;
        node->count++;
        for (int i = N-1; i >= 0; i--) {
            int d = (x >> i) & 1;
            if (node->children[d] == NULL) {
                node->children[d] = new Node();
            }
            node = node->children[d];
            node->count++;
        }
    }
};

