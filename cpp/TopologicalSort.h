#include <stack>
/** Topological sort
  * usage example:
    // set up DirectedGraph g
    vector<int> topo = TopologicalSort::sort(g);
 */
// Note: be sure it's DAG
class TopologicalSort {
private:
    static void topologicalSortUtil(const DirectedGraph& g,
                                    int v, bool visited[],
                                    stack<int> &order) {
        visited[v] = true;

        const vector<int>& outNodes = g.outNodes(v);
        for (int m: outNodes) {
            if (!visited[m]) {
                topologicalSortUtil(g, m, visited, order);
            }
        }

        order.push(v);
    }

public:
    static vector<int> sort(const DirectedGraph& g) {
        vector<int> topo;
        stack<int> order;
        int N = g.size();
        bool visited[N];
        for (int i = 0; i < N; i++) {
            visited[i] = false;
        }

        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                topologicalSortUtil(g, i, visited, order);
            }
        }

        while (!order.empty()) {
            topo.push_back(order.top());
            order.pop();
        }
        return topo;
    }
};

