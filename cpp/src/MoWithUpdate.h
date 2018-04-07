class MoWithUpdate {
    struct Query {
        int l, r, t, id;
        int bl_id, br_id;

        bool operator < (const Query &other) const {
            if (bl_id < other.bl_id) return true;
            if (bl_id > other.bl_id) return false;
            if (br_id < other.br_id) return true;
            if (br_id > other.br_id) return false;
            if (t < other.t) return true;
            if (t > other.t) return false;
            return id < other.id;
        }
    };

private:
    int N;
    int BLOCK_SIZE;
    vector<Query> queries;
    int updIdx = 0;
    int id = 0;
    int nowAns = 0, lcurr = 0, rcurr = 0, tcurr = 0;

    // custmize the following
    struct Update {
        int x, c;
    };
    vector<Update> updates;

    void move(int pos, int sign) {
        int c = color[pos];
        if (sign == -1) {
            if (--cnt[c] == 0) nowAns--;
        } else {
            if (++cnt[c] == 1) nowAns++;
        }
    }

    void moveTime(int t, int sign) {
        int x = updates[t].x;
        int c = updates[t].c;
        if (lcurr <= x && x < rcurr) {
            int cp = color[x];
            if (--cnt[cp] == 0) nowAns--;
            if (++cnt[c] == 1) nowAns++;
        }
        color[x] = c;
    }

public:
    vector<int> ans;

    vector<int> color;
    vector<int> cnt;

public:
    MoWithUpdate(int N_): N(N_) {
        BLOCK_SIZE = int(ceil(pow(N, 2.0/3)));
    }

    void addQuery(int l, int r) {
        int bl_id = l/BLOCK_SIZE;
        int br_id = r/BLOCK_SIZE;
        Query q{l, r, updIdx, id++, bl_id, br_id};
        queries.push_back(q);
    }

    void addUpdate(int x, int c) {
        Update upd{x, c};
        updates.push_back(upd);
        updIdx++;
    }

    void solve() {
        const int M = queries.size();
        ans.resize(M);
        sort(queries.begin(), queries.end());
        for (const auto &q: queries) {
            while (tcurr < q.t) moveTime(tcurr++, 1);
            while (tcurr > q.t) moveTime(--tcurr, -1);
            while (lcurr < q.l) move(lcurr++, -1);
            while (lcurr > q.l) move(lcurr--, 1);
            while (rcurr < q.r) move(rcurr++, 1);
            while (rcurr > q.r) move(--rcurr, -1);
            ans[q.id] = nowAns;
        }
    }
};
