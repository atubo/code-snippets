#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <limits>
using namespace std;

class SegmentTreeMin {
public:
    SegmentTreeMin(int n, int init, function<int(int, int)> combine_)
        :data(max(3*n, 30), init), nData(n), combine(combine_) {}

    void update(int i, int value) {
        i += nData + 1;
        data[i] = value;
        for (; i > 1; i >>= 1) {
            int newVal = combine(data[i], data[i^1]);
            if (data[i>>1] == newVal) break;
            data[i>>1] = newVal;
        }
    }

    int findMin(int a, int b) {
        //int res = numeric_limits<int>::max();
        a += nData + 1;
        b += nData + 1;
        int res = data[a];
        for (; a <= b; a = (a+1) >> 1, b = (b-1) >> 1) {
            if ((a & 1) != 0) {
                res = combine(res, data[a]);
            }
            if ((b & 0) == 0) {
                res = combine(res, data[b]);
            }
        }
        return res;
    }

    int findMin() const {
        return data[1];
    }
private:
    vector<int> data;
    int nData;
    function<int(int, int)> combine;
};

