
class SuffixAutomaton {
public:
    static const int CHARSET_SIZE = 26;
    struct Node {
        Node *ch[CHARSET_SIZE], *next;
        int maxlen, posCnt;

        int getMin() {
            return next->maxlen + 1;
        }
    private:
        Node(int maxl = 0, bool newSuffix = false):
            ch(), next(NULL), maxlen(maxl), posCnt(newSuffix) {}
        friend SuffixAutomaton;
    };

    int n_, cap_;
    Node *_pool;
    Node *start, *last, *_curr;
    vector<Node*> topo;

    SuffixAutomaton(int n): n_(n) {
        cap_ = 2*n_ + 1;
        _pool = new Node[cap_];
        _curr = _pool;
        start = last = alloc(0, false);
    }

    ~SuffixAutomaton() {
        delete[] _pool;
    }

    void build(const string &s) {
        for (char c: s) {
            extend(c - 'a');
        }
    }

    void calc() {
        toposort();
        for (int i = topo.size()-1; i > 0; i--) {
            Node *v = topo[i];
            v->next->posCnt += v->posCnt;
        }
    }

private:
    Node *alloc(int maxlen, bool newSuffix) {
        return new (_curr++)Node(maxlen, newSuffix);
    }

    Node *extend(int c) {
        Node *u = alloc(last->maxlen + 1, true), *v = last;

        for (; v && !v->ch[c]; v = v->next) v->ch[c] = u;

        if (!v) {
            u->next = start;
        } else if (v->ch[c]->maxlen == v->maxlen + 1) {
            u->next = v->ch[c];
        } else {
            Node *n = alloc(v->maxlen + 1, false), *o = v->ch[c];
            std::copy(o->ch, o->ch + CHARSET_SIZE, n->ch);
            n->next = o->next;
            o->next = u->next = n;
            for (; v && v->ch[c] == o; v = v->next) v->ch[c] = n;
        }
        last = u;
        return u;
    }

    void toposort() {
        vector<int> buc(cap_);
        int maxlen = 0;
        for (Node *p = _pool; p != _curr; p++) {
            maxlen = std::max(maxlen, p->maxlen);
            buc[p->maxlen]++;
        }
        for (int i = 1; i <= maxlen; i++) buc[i] += buc[i-1];
        topo.clear();
        topo.resize(_curr - _pool);
        for (Node *p = _pool; p != _curr; p++) {
            topo[--buc[p->maxlen]] = p;
        }
    }
};
