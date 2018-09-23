
class ExtendedSuffixAutomaton {
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
        friend ExtendedSuffixAutomaton;
    };

    int n_, cap_;
    Node *_pool;
    Node *start, *last, *_curr;
    vector<Node*> topo;

    ExtendedSuffixAutomaton(int n): n_(n) {
        cap_ = 2*n_ + 1;
        _pool = new Node[cap_];
        _curr = _pool;
        start = last = alloc(0, false);
    }

    ~ExtendedSuffixAutomaton() {
        delete[] _pool;
    }

    /**
     * @param p: current position in this SAM
     * @param c: new character to be inserted
     * @return: new position after insertion
     */
    Node* ins(Node* p, int c) {
        if (p->ch[c]) {
            last = split(p, c);
        } else {
            Node *np = alloc(p->maxlen+1, true);
            last = np;
            for (; p && !p->ch[c]; p = p->next) p->ch[c] = np;
            if (!p) np->next = start;
            else np->next = split(p, c);
        }
        return last;
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

    /**
     * split p->ch[c] if necessary
     * @param p: a node whose transition state on c will be splitted if needed
     * @param c: transition character
     * @return: if split happens return the new node, otherwise the old node
     */
    Node* split(Node *p, int c) {
        Node *q = p->ch[c];
        if (q->maxlen == p->maxlen+1) return q;

        Node *nq = alloc(p->maxlen+1, false);
        std::copy(q->ch, q->ch + CHARSET_SIZE, nq->ch);
        nq->next = q->next;
        q->next = nq;
        for (; p && p->ch[c] == q; p = p->next) p->ch[c] = nq;
        return nq;
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
