class ExtChineseRemainder {
private:
    int64_t b_ = 0, m_ = 1;
public:
    ExtChineseRemainder() {}

    bool add(int64_t b2, int64_t m2) {
        int64_t g, u, v;
        ModularUtils::ext_gcd(m_, m2, g, u, v);
        if (b_ % g != b2 % g) return false;
        int64_t lcm = m2 / g * m_;
        int64_t t1 = ModularUtils::mul_long(m2/g, b_, lcm);
        t1 = ModularUtils::mul_long(t1, v, lcm);
        int64_t t2 = ModularUtils::mul_long(m_/g, b2, lcm);
        t2 = ModularUtils::mul_long(t2, u, lcm);
        b_ = ((t1 + t2) % lcm + lcm) % lcm;
        m_ = lcm;
        return true;
    }

    int64_t get() const { return b_; }
};
