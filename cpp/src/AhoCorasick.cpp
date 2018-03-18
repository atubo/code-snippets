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
public:
    const static int MAXN = 1e6 + 42;

    vector<map<char, int> > to;
    vector<set<int> > out;
    int sz = 1;
    int *link;  // blue link in the wiki
    int *next;  // green link in the wiki
    int *que;
    int keywordIndex;

    AhoCorasick(): to(MAXN), out(MAXN), keywordIndex(0) {
        link = new int[MAXN]{};
        next = new int[MAXN]{};
        que  = new int[MAXN]{};
    }

    ~AhoCorasick() {
        delete[] link;
        delete[] next;
        delete[] que;
    }

    void add_str(const string &s) {
        int v = 0;
        for(auto c: s) {
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
            for(auto it: to[v]) {
                int u = it.second;
                int c = it.first;
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
            char c = t[i];
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
    int followDictSuffixLink(int q) {
        int res = 0;
        while (q != 0) {
            res += out[q].size();
            q = next[q];
        }
        return res;
    }
};
