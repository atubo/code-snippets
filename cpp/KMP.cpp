#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class KMP {
public:
    KMP(const string& str):f(str.length(), 0) {
        int t = 0;
        f[0] = 0;

        // prefix function
        for (int s = 1; s < (int)str.length(); s++) {
            while (t > 0 && str[s] != str[t]) {
                t = f[t-1];
            }
            if (str[s] == str[t]) {
                t++;
            }
            f[s] = t;
        }
    }

    int operator[](int i) const {
        return f[i];
    }

private:
    vector<int> f;
};
