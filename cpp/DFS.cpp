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
        const int N = graph.size();
        vector<bool> marked(N, false);
        vector<int> visited(N, 0);
        stack<int> st;
        push(v, st, marked, pre);
        while (!st.empty()) {
            int u = st.top();
            const vector<int>& neighbors = graph.getAdj(u);
            if (visited[u] < (int)neighbors.size()) {
                int w = neighbors[visited[u]];
                visited[u]++;
                if (!marked[w]) {
                    push(w, st, marked, pre);
                }
            } else {
                pop(u, st, post);
            }
        }
    }

private:
    static void push(int v,
                     stack<int>& st,
                     vector<bool>& marked,
                     function<void(int)> pre) {
        marked[v] = true;
        pre(v);
        st.push(v);
    }

    static void pop(int v,
                    stack<int>& st,
                    function<void(int)> post) {
        post(v);
        st.pop();
    }
};

