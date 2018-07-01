// segment tree with single point update and range query
// 0-indexed
class SegmentTreeSPU {
    static const int NULL_VALUE = 0;
public:
    SegmentTreeSPU(int n) {
        nData_ = 1;
        while (nData_ < n) nData_ = nData_ << 1;
        int sz = 2 * nData_ + 1;
        data = new int[sz];
        for (int i = 0; i < sz; i++) data[i] = NULL_VALUE;
    }

    ~SegmentTreeSPU() {
        delete[] data;
    }

    void update(int i, int value) {
        i += nData_;
        data[i] = value;
        for (; i > 1; i >>= 1) {
            int newVal = combine(data[i], data[i^1]);
            if (data[i>>1] == newVal) break;
            data[i>>1] = newVal;
        }
    }

    void build() {
        // assume all leaf nodes are already set up
        for (int i = nData_-1; i >= 1; i--) {
            data[i] = combine(data[2*i], data[2*i+1]);
        }
    }

    int query(int a, int b) const {
        a += nData_;
        b += nData_;
        int res = NULL_VALUE;
        for (; a <= b; a = (a+1) >> 1, b = (b-1) >> 1) {
            if ((a & 1) != 0) {
                res = combine(res, data[a]);
            }
            if ((b & 1) == 0) {
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
    int nData_;
    int combine(int a, int b) const {
        return a + b;
    }
};
