class Mask {
    // 1000-bit
    static const int SZ = 32;
private:
    unsigned int bits[SZ];
public:
    Mask() {
        memset(bits, 0, sizeof(bits));
    }

    void set(int i) {
        bits[i/32] |= (1 << (i%32));
    }

    void unset(int i) {
        bits[i/32] &= ~(1 << (i%32));
    }

    int get(int i) const {
        // return 0 or 1
        return (bits[i/32] >> (i%32)) & 1;
    }

    Mask& operator |= (const Mask &other) {
        for (int i = 0; i < SZ; i++) {
            bits[i] |= other.bits[i];
        }
        return *this;
    }

    Mask& operator ^= (const Mask &other) {
        for (int i = 0; i < SZ; i++) {
            bits[i] ^= other.bits[i];
        }
        return *this;
    }

    int popcount() {
        int ret = 0;
        for (int i = 0; i < SZ; i++) {
            ret += __builtin_popcount(bits[i]);
        }
        return ret;
    }

    string toString(int n) {
        string ret(n, '0');
        for (int i = 0; i < n; i++) {
            ret[n-1-i] = get(i) + '0';
        }
        return ret;
    }
};
