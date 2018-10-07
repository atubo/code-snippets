
// internal arrays are 1-based
// assume no duplicated elements
class Sbt {
public:
    Sbt(int n): n_(n+1) {
        alloc();
    }

    ~Sbt() {
        dealloc();
    }

    void insert(int v) {
        insert(root_, v);
    }

    int rank(int v) const {
        return rank(root_, v);
    }


private:
    int n_;
    int *key_;
    int *size_;
    int **sons_;
    int tail_ = 0;
    int root_ = 0;

    void alloc() {
        key_ = new int[n_]{};
        size_ = new int[n_]{};
        sons_ = new int*[n_]{};
        for (int i = 0; i < n_; i++) sons_[i] = new int[2]{};
    }

    void dealloc() {
        delete[] key_;
        delete[] size_;
        for (int i = 0; i < n_; i++) delete[] sons_[i];
        delete[] sons_;
    }

    void rotate(int &t, int w) {
        int k = sons_[t][1-w];
        if (!k) return;
        sons_[t][1-w] = sons_[k][w];
        sons_[k][w] = t;
        size_[k] = size_[t];
        size_[t] = size_[sons_[t][0]] + size_[sons_[t][1]] + 1;
        t = k;
    }

    void maintain(int &t, bool flag) {
        if (!t) return;
        if (!flag) {
            if (size_[sons_[sons_[t][0]][0]] > size_[sons_[t][1]]) {
                rotate(t, 1);
            } else if (size_[sons_[sons_[t][0]][1]] > size_[sons_[t][1]]) {
                rotate(sons_[t][0], 0);
                rotate(t, 1);
            } else {
                return;
            }
        } else {
            if (size_[sons_[sons_[t][1]][1]] > size_[sons_[t][0]]) {
                rotate(t, 0);
            } else if (size_[sons_[sons_[t][1]][0]] > size_[sons_[t][0]]) {
                rotate(sons_[t][1], 1);
                rotate(t, 0);
            } else {
                return;
            }
        }

        maintain(sons_[t][0], false);
        maintain(sons_[t][1], true);
        maintain(t, false);
        maintain(t, true);
    }

    void insert(int &t, int v) {
        if (!size_[t]) {
            int pos = ++tail_;
            key_[pos] = v;
            size_[pos] = 1;
            sons_[pos][0] = sons_[pos][1] = 0;
            t = pos;
        } else {
            size_[t]++;
            if (v < key_[t]) insert(sons_[t][0], v);
            else insert(sons_[t][1], v);
            maintain(t, v>=key_[t]);
        }
    }

    int rank(int t, int v) const {
        if (t == 0) return 0;
        if (v == key_[t]) return size_[sons_[t][0]];
        if (v < key_[t]) return rank(sons_[t][0], v);
        return 1 + size_[sons_[t][0]] + rank(sons_[t][1], v);
    }
};
