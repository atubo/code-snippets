// templates for Mo's algorithm
// see https://blog.sengxian.com/algorithms/mo-s-algorithm

class Mo {
    struct Query {
        int l, r, id;
        int block_id;
        int x;

        bool operator < (const Query& other) const {
            return make_pair(block_id, r) < make_pair(other.block_id, other.r);
        }
    };

private:
    int N_, Q_;
    int currId_ = 0;
    int BLOCK_SIZE;
    Query *queries_;
    int *cnt_;

    void move(int pos, int sign) {
        if (sign == 1) cnt_[elem[pos]]++;
        else cnt_[elem[pos]]--;
    }

    void alloc() {
        queries_ = new Query[Q_]{};
        cnt_ = new int[N_+1]{};

        elem = new int[N_]{};
        ans  = new int[Q_]{};
    }

    void dealloc() {
        delete[] queries_;
        delete[] cnt_;

        delete[] elem;
        delete[] ans;
    }

public:
    int *elem;
    int *ans;

    Mo(int N, int Q): N_(N), Q_(Q) {
        BLOCK_SIZE = int(ceil(pow(N_, 0.5)));
        alloc();
    }

    ~Mo() {
        dealloc();
    }

    void addQuery(int l, int r, int x) {
        queries_[currId_] = {l, r, currId_, l/BLOCK_SIZE, x};
        currId_++;
    }

    void solve() {
        sort(queries_, queries_+Q_);

        int l = 0, r = 0;
        // put other initializations here

        for (int i = 0; i < Q_; i++) {
            const Query& q = queries_[i];
            while (l > q.l) move(--l, 1);
            while (r < q.r) move(r++, 1);
            while (l < q.l) move(l++, -1);
            while (r > q.r) move(--r, -1);
            ans[q.id] = cnt_[q.x];
        }
    }
};

// Extend to right side permanently and to left side tentatively
// see http://www.voidcn.com/blog/a_crazy_czy/article/p-6178819.html
class Mo2 {
    struct Query {
        int l, r, id;
        int block_id;

        bool operator < (const Query& other) const {
            return make_pair(block_id, r) < make_pair(other.block_id, other.r);
        }
    };

private:
    int N;
    int currAns, BLOCK_SIZE;
    vector<Query> queries;
    vector<int> ans;
    int lcur, rcur;

    void add(int x, bool tp) {
        if (lcur >= rcur) return;
        // update currAns
        if (tp) {
            // tentative add
        } else {
            // permanent add
        }
    }

    void rollback() {
        // implementation here
    }

public:
    void setUp() {
        BLOCK_SIZE = int(ceil(pow(N, 0.5)));
        // set up queries;

        ans.resize(queries.size());
    }

    void solve() {
        sort(queries.begin(), queries.end());

        for (int i = 0, tail; i < (int)queries.size(); i++) {
            const Query& q = queries[i];
            if (i == 0 || q.block_id != queries[i-1].block_id) {
                // initialize permanent part and currAns
                lcur = tail = min((q.block_id+1) * BLOCK_SIZE, N);
                rcur = 0;
            }
            while (rcur < q.r) add(rcur++, 0);
            int tmp = currAns;
            while (lcur > q.l) add(--lcur, 1);
            ans[q.id] = currAns;
            currAns = tmp;
            rollback();
            lcur = tail;
        }
    }
};
