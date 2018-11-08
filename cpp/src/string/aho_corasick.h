#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

/** Class to do multiple-pattern matching
  * usage example:
    AhoCorasick ac;
    ac.add_str(string("he"));
    ac.add_str(string("she"));
    ac.add_str(string("his"));
    ac.add_str(string("hers"));
    ac.push_links();

    cout << ac.countTotalMatches(string("shershishe")) << endl;

    Please see
    1. http://www.cs.uku.fi/~kilpelai/BSA05/lectures/slides04.pdf
    2. http://codeforces.com/blog/entry/14854
    3. https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm
 */
class AhoCorasick {
    static constexpr const char *ALPHABET = "abcdefghijklmnopqrstuvwxyz";
    static const int ALPHA_SIZE = strlen(ALPHABET);
public:
    const int n_;
    int **to;
    vector<set<int> > out;
    int sz = 1;
    int *link;  // blue link in the wiki
    int *next;  // green link in the wiki
    int *que;
    int keywordIndex;

    // n is total length, total number of nodes is at most n+1
    AhoCorasick(int n): n_(n+1), out(n_), keywordIndex(0) {
        to = new int*[n_]{};
        for (int i = 0; i < n_; i++) {
            to[i] = new int[ALPHA_SIZE]{};
        }

        link = new int[n_]{};
        next = new int[n_]{};
        que  = new int[n_]{};
    }

    ~AhoCorasick() {
        for (int i = 0; i < n_; i++) {
            delete[] to[i];
        }
        delete[] to;

        delete[] link;
        delete[] next;
        delete[] que;
    }

    void add_str(const string &s) {
        int v = 0;
        for(int i = 0; i < (int)s.length(); i++) {
            int c = s[i] - ALPHABET[0];
            if(!to[v][c]) to[v][c] = sz++;
            v = to[v][c];
        }
        out[v].insert(keywordIndex++);
    }

    void push_links() {
        link[0] = -1;
        int st = 0, fi = 1;
        que[0] = 0;
        while (st < fi) {
            int v = que[st++];
            for (int c = 0; c < ALPHA_SIZE; c++) {
                int u = to[v][c];
                if (u == 0) continue;
                int j = link[v];
                while(j != -1 && !to[j][c]) j = link[j];
                if(j != -1) link[u] = to[j][c];
                if (out[link[u]].empty()) {
                    next[u] = next[link[u]];
                } else {
                    next[u] = link[u];
                }
                que[fi++] = u;
            }
        }
    }

    int countTotalMatches(const string &t) {
        int result = 0;
        int q = 0;
        for (int i = 0; i < (int)t.length(); i++) {
            int c = t[i] - ALPHABET[0];
            while (q != -1 && to[q][c] == 0) {
                q = link[q];
            }
            if (q != -1) {
                q = to[q][c];
                result += followDictSuffixLink(q);
            } else {
                q = 0;
            }
        }
        return result;
    }

private:
    int followDictSuffixLink(int q) const {
        int res = 0;
        while (q != 0) {
            res += out[q].size();
            q = next[q];
        }
        return res;
    }
};
