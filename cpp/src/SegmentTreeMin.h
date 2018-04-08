class SegmentTreeMin {
public:
    SegmentTreeMin(int n, int init = 0) :nData(n) {
        int sz = max(3*n, 30);
        data = new int[sz]{init};
    }

    ~SegmentTreeMin() {
        delete[] data;
    }

    void update(int i, int value) {
        i += nData + 1;
        data[i] = value;
        for (; i > 1; i >>= 1) {
            int newVal = combine(data[i], data[i^1]);
            if (data[i>>1] == newVal) break;
            data[i>>1] = newVal;
        }
    }

    int query(int a, int b) const {
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

    int query() const {
        return data[1];
    }
private:
    int *data;
    int nData;
    int combine(int a, int b) const {
        return min(a, b);
    }
};
