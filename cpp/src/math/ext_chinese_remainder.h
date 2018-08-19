class ExtChineseRemainder {
private:
    bool started_ = false;
    int64_t b_, m_;
public:
    ExtChineseRemainder() {}

    bool add(int64_t b2, int64_t m2) {
        if (!started_) {
            b_ = b2;
            m_ = m2;
            started_ = true;
            return true;
        }

        int64_t g, u, v;
        ModularUtils::ext_gcd(m_, m2, g, u, v);
        if (b_ % g != b2 % g) return false;
        b_ = m2 / g * b_ *v + m_ / g * b2 * u;
        m_ = m2 / g * m_;
        b_ = (b_ % m_ + m_) % m_;
        return true;
    }

    int64_t get() const { return b_; }
};
