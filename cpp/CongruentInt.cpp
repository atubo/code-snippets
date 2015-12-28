#include <cinttypes>

using namespace std;

/**
 * A class to do calculations and keep a result congruent to
 * a fixed prime number
 */
class CongruentInt {
private:
    int64_t val;
    int MOD;
public:
    CongruentInt(int64_t val_, int MOD_):val(val_), MOD(MOD_) {
        val = val % MOD;
    }

    explicit operator int64_t() const {
        return val;
    }

    CongruentInt& operator *= (int mul) {
        val = val * mul % MOD;
        return *this;
    }
};

