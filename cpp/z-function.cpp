#include <string>
#include <vector>
using namespace std;

vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

/* https://www.hackerrank.com/challenges/string-similarity/topics/z-function
   Suppose we are given a string s of length n. The Z-function for this string is an array of length n where the i-th element is equal to the greatest number of characters starting from the position i that coincide with the first characters of s.

Examples:
s = 'aaaaa'
z = [0,4,3,2,1]

s =  'aaabaab'
z = [0,2,1,0,2,1,0]

s = 'abacaba'
z = [0,0,1,0,3,0,1]
*/
