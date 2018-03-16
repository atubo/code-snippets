
class SuffixAutomaton {
public:
    static const int CHARSET_SIZE = 26;
    static const int MAXN = 1000;
    struct Node {
        Node *ch[CHARSET_SIZE], *next;
        int max, posCnt;

        Node(int max = 0, bool newSuffix = false):
            ch(), next(NULL), max(max), posCnt(newSuffix) {}

        int getMin() {
            return next->max + 1;
        }
    };

    Node *start, *last, *_curr;
    Node _pool[MAXN * 2 + 1];
    vector<Node*> topo;

    SuffixAutomaton() {
        _curr = _pool;
        start = last = new (_curr++)Node;
    }

    Node *extend(int c) {
        Node *u = new (_curr++)Node(last->max + 1, true), *v = last;

        for (; v && !v->ch[c]; v = v->next) v->ch[c] = u;

        if (!v) {
            u->next = start;
        } else if (v->ch[c]->max == v->max + 1) {
            u->next = v->ch[c];
        } else {
            Node *n = new (_curr++)Node(v->max + 1, false), *o = v->ch[c];
            std::copy(o->ch, o->ch + CHARSET_SIZE, n->ch);
            n->next = o->next;
            o->next = u->next = n;
            for (; v && v->ch[c] == o; v = v->next) v->ch[c] = n;
        }
        last = u;
        return u;
    }

    void toposort() {
        topo.clear();
        topo.resize(_curr - _pool);
        for (int i = 0; i < _curr - _pool; i++) {
            topo[i] = &_pool[i];
        }
        sort(topo.begin(), topo.end(), [](const Node *a, const Node *b) {
             return a->max < b->max;
             });
    }

    void calc() {
        toposort();
        for (int i = topo.size()-1; i > 0; i--) {
            Node *v = topo[i];
            v->next->posCnt += v->posCnt;
        }
    }
};
