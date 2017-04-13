#include <functional>
#include <stack>
#include <vector>

using namespace std;

// Do DFS on the given graph
//
// pre and post are lambdas that are called
// when a node is pushed onto the stack and
// popped out of the stack respectively
// 
// note that a node is only popped out when all its decendants
// have been visited
class DFS {
public:
    static void dfs(const Graph& graph,
                    int v,
                    function<void(int)> pre,
                    function<void(int)> post) {
        const int N = graph.N;
        vector<bool> visited(N);
        dfs(graph, v, visited, pre, post);
    }

private:
    static void dfs(const Graph &g,
                    int u,
                    vector<bool> &visited,
                    function<void(int)> pre,
                    function<void(int)> post) {
        visited[u] = true;
        pre(u);
        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (!visited[v]) {
                dfs(g, v, visited, pre, post);
            }
        }
        post(u);
    }
};

