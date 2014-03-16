// Code based on http://www.akalin.cx/longest-palindrome-linear-time
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class LongestPalindromicSubstr
{
public:
    LongestPalindromicSubstr(const string& seq_)
        :seq(seq_) {}
    pair<int, int> getLPSubstr() const {
        if (seq.size() == 0) {
            return make_pair(0, 0);
        }
        vector<int> l = getLengthArray(seq);
        vector<int>::const_iterator it = max_element(l.begin(),
                                                     l.end());
        int pos = it - l.begin();
        return make_pair(pos/2-l[pos]/2, l[pos]);
    }

    static vector<int> getLengthArray(const string& seq) {
        int seqLen = seq.length();
        vector<int> l;
        int i = 0;
        int parLen = 0;
        while (i < seqLen) {
START_OF_WHILE:
            if (i > parLen && seq[i - parLen - 1] == seq[i]) {
                parLen += 2;
                i++;
                continue;
            }
            l.push_back(parLen);

            int s = l.size() - 2;
            int e = s - parLen;
            for (int j = s; j > e; j--) {
                int d = j - e - 1;
                if (l[j] == d) {
                    parLen = d;
                    goto START_OF_WHILE;
                }
                l.push_back(min(d, l[j]));
            }
            parLen = 1;
            i++;
        }
        l.push_back(parLen);
        int lLen = l.size();
        int s = lLen - 2;
        int e = s - (2 * seqLen + 1 - lLen);
        for (int j = s; j > e; j--) {
            int d = j - e - 1;
            l.push_back(min(d, l[j]));
        }

        return l;
    }

private:
    const string& seq;
};
