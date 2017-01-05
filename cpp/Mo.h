
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
