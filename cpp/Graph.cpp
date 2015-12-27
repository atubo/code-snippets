#include <iostream>
#include <vector>

using namespace std;

// Undirected graph
// Note graph node is 0-indexed
class Graph {
private:
    const int N;
    vector<vector<int> > adj;
public:
    Graph(int N_):N(N_) {
        adj.resize(N);
    }

    // assume 0-indexed and no duplication
    void addEdge(int i, int j) {
        adj[i].push_back(j);
        adj[j].push_back(i);
    }

    int size() const {return N;}

    const vector<int>& getAdj(int i) const {
        return adj[i];
    }
};
