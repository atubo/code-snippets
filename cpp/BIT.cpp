#include <cinttypes>
#include <cstring>
#include <cstdlib>
using namespace std;

class BIT {
public:
    BIT(int size): N(size) {
        tree = (int64_t*)malloc((size+1) * sizeof(int64_t));
        memset(tree, 0, (size+1) * sizeof(int64_t));
    }
    
    ~BIT() {
        free(tree);
        tree = NULL;
    }
    // add v to value at x
    void set(int x, int v) {
        while(x <= N) {
            tree[x] += v;
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int64_t get(int x) {
        int64_t res = 0;
        while(x) {
            res += tree[x];
            x -= (x & -x);
        }
        return res;
    }

    // get largest value with cumulative sum less than or equal to x;
    // for smallest, pass x-1 and add 1 to result
    int getind(int x) {
        int idx = 0, mask = N;
        while(mask && idx < N) {
            int t = idx + mask;
            if(x >= tree[t]) {
                idx = t;
                x -= tree[t];
            }
            mask >>= 1;
        }
        return idx;
    }

private:
    int64_t* tree;
    const int N;
};
