class HashSet {
    static const int MAXM = 1000003;
    static int GARBAGE;

    struct Node {
        pair<int, int> to;
        int next, cnt;
    };
public:
    HashSet(int n) {
        alloc(n);
        sz_ = 0;
    }

    ~HashSet() {
        dealloc();
    }

    bool contains(const pair<int, int> &x) {
        int y = x.first % MAXM;
        for (int i = h_[y]; i; i = e_[i].next) {
            auto to = e_[i].to;
            if (to == x) return true;
        }
        return false;
    }

    int& operator[](const pair<int, int> &x) {
        int y = x.first % MAXM;
        for (int i = h_[y]; i; i = e_[i].next) {
            auto to = e_[i].to;
            if (to == x) return e_[i].cnt;
        }
        return GARBAGE;
    }

    void insert(const pair<int, int> &x) {
        int y = x.first % MAXM;
        e_[++sz_] = Node{x, h_[y], 1};
        h_[y] = sz_;
    }

    void reset() {
        memset(h_, 0, MAXM*sizeof(int));
        sz_ = 0;
    }
private:
    Node *e_;
    int *h_;
    int sz_;

    void alloc(int n) {
        e_ = new Node[n]{};
        h_ = new int[MAXM]{};
    }

    void dealloc() {
        delete[] e_;
        delete[] h_;
    }
};

int HashSet::GARBAGE = 0;

const int P = 347;
const int Q = 997;
const int MOD1 = 1e9+7;
const int MOD2 = 1e9+9;
void hashf(pair<int, int> &p, int x) {
    p.first = (1LL*p.first * P + x) % MOD1;
    p.second = (1LL*p.second * Q + x) % MOD2;
}

