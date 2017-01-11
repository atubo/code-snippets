
// templates for Mo's algorithm
// see https://blog.sengxian.com/algorithms/mo-s-algorithm

class Mo {
    struct Query {
        int l, r, id;
        int block_id;

        bool operator < (const Query& other) const {
            return make_pair(block_id, r) < make_pair(other.block_id, other.r);
        }
    };

private:
    int N;
    int nowAns, BLOCK_SIZE;
    vector<Query> queries;
    vector<int> ans;

    void move(int pos, int sign) {
        // update nowAns
    }

public:
    void setUp() {
        BLOCK_SIZE = int(ceil(pow(N, 0.5)));
        // set up queries;

        ans.resize(queries.size());
    }

    void solve() {
        sort(queries.begin(), queries.end());

        int l = 0, r = 0;
        // and put initialization here,
        // such as nowAns = 0;

        for (int i = 0; i < (int)queries.size(); i++) {
            const Query& q = queries[i];
            while (l > q.l) move(--l, 1);
            while (r < q.r) move(r++, 1);
            while (l < q.l) move(l++, -1);
            while (r > q.r) move(--r, -1);
            ans[q.id] = nowAns;
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
    int nowAns, BLOCK_SIZE;
    vector<Query> queries;
    vector<int> ans;
    int lcur, rcur;

    void add(int x, bool tp) {
        if (lcur >= rcur) return;
        // update nowAns
        if (tp) {
            // tentative add
        } else {
            // permanent add
        }
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
                // initialize permanent part and nowAns
                lcur = tail = min((q.block_id+1) * BLOCK_SIZE, N);
                rcur = 0;
            }
            while (rcur < q.r) add(rcur++, 0);
            int tmp = nowAns;
            while (lcur > q.l) add(--lcur, 1);
            ans[q.id] = nowAns;
            nowAns = tmp;
            rollback();
            lcur = tail;
        }
    }
};
