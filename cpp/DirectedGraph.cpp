#include <cassert>
#include <vector>

using namespace std;

class DirectedGraph {
private:
    int N;
    vector<vector<int> > in;
    vector<vector<int> > out;
public:
    DirectedGraph(int N_):N(N_) {
        in.resize(N);
        out.resize(N);
    }

    int size() const {
        return N;
    }

    // add edge u->v
    void addEdge(int u, int v) {
        assert(0 <= u && 0 <= v && u < N && v < N);
        in[v].push_back(u);
        out[u].push_back(v);
    }

    const vector<int>& inNodes(int u) const {
        return in[u];
    }

    const vector<int>& outNodes(int u) const {
        return out[u];
    }
};

