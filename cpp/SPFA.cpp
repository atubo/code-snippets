#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

typedef vector<map<int, int>> Adj;

class SPFA {
    const static int64_t INF;

public:
    SPFA(const Adj& adj_):adj(adj_) {
        N = adj.size();
    }

    void init(int src) {
        while (!Q.empty()) Q.pop();
        inq.clear();
        dist.clear();
        path.clear();

        inq.resize(N, 0);
        dist.resize(N, INF);
        path.resize(N, src);

        dist[src] = 0;
        inq[src]++;
    }

    void solve(int src) {
        init(src);

        Q.push(src);
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            inq[u]--;

            for (const auto& nbr: adj[u]) {
                int v;
                int64_t w;
                tie(v, w) = nbr;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    path[v] = u;
                    if (!inq[v]) {
                        Q.push(v);
                        inq[v]++;
                    }
                }
            }
        }
    }

    const vector<int64_t>& getDist() const {return dist;}

    const vector<int>& getPath() const {return path;}

private:
    const Adj& adj;
    queue<int> Q;
    int N;
    vector<int> inq;    // if node is in queue
    vector<int64_t> dist;
    vector<int> path;
};

const int64_t SPFA::INF = LLONG_MAX/4;
