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
 */
class AhoCorasick {
public:
    const static int MAXN = 1e6 + 42;

    vector<map<char, int> > to;
    vector<set<int> > out;
    int link[MAXN], que[MAXN], sz = 1;
    int keywordIndex;

    AhoCorasick():
        to(MAXN), out(MAXN), keywordIndex(0) {
        memset(link, 0, MAXN*sizeof(int));
        memset(que,  0, MAXN*sizeof(int));

    }

    void add_str(string s)
    {
        int v = 0;
        for(auto c: s)
        {
            if(!to[v][c]) to[v][c] = sz++;
            v = to[v][c];
        }
        out[v].insert(keywordIndex++);
    }

    void push_links()
    {
        link[0] = -1;
        int st = 0, fi = 1;
        que[0] = 0;
        while(st < fi)
        {
            int v = que[st++];
            for(auto it: to[v])
            {
                int u = it.second;
                int c = it.first;
                int j = link[v];
                while(j != -1 && !to[j][c]) j = link[j];
                if(j != -1) link[u] = to[j][c];
                out[u].insert(out[link[u]].begin(), out[link[u]].end());
                que[fi++] = u;
            }
        }
    }

    int countTotalMatches(const string& T) {
        int result = 0;
        int q = 0;
        for (int i = 0; i < (int)T.length(); i++) {
            char c = T[i];
            while (q != -1 && to[q][c] == 0) {
                q = link[q];
            }
            if (q != -1) {
                q = to[q][c];
                if (!out[q].empty()) {
                    result += out[q].size();
                }
            } else {
                q = 0;
            }
        }
        return result;
    }
};
