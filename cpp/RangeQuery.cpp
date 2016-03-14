#include <cinttypes>
#include <set>

using namespace std;

// Data structure to provide operations
// 1. put/delete an integer
// 2. answer queries like how many elements are there in the range [a, b)
template <typename T>
class RangeQuery {
public:
    RangeQuery() = default;
    RangeQuery(const RangeQuery&) = default;
    ~RangeQuery() = default;

    void put(T x) {
        data.insert(x);
    }

    void remove(T x) {
        // note that if x is not there, the function quitely returns
        auto it = data.find(x);
        data.erase(it);
    }

    // if there is element in [a, b)
    bool hasElementIn(T a, T b) const {
        // first element >= a
        const auto it1 = data.lower_bound(a);
        const auto it2 = data.lower_bound(b);
        return it1 != it2;
    }

private:
    multiset<T> data;
};
