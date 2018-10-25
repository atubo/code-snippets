
// For directed graph
class Hierholzer {
public:
    Hierholzer(int n): n_(n), edges_(n) {}

    void addEdge(int u, int v) {
        edges_[u].push_back(v);
    }

    vector<int> solve(int s) {
        vector<int> path;
        vector<deque<int>> edges = edges_;  // make a copy
        stack<int> st;
        st.push(s);
        while (!st.empty()) {
            int u = st.top();
            st.pop();
            if (!edges[u].empty()) {
                dfs(u, edges, st);
            } else {
                path.push_back(u);
            }
        }
        reverse(path.begin(), path.end());
        return path;
    }

private:
    int n_;
    vector<deque<int>> edges_;

    void dfs(int u, vector<deque<int>> &edges, stack<int> &st) {
#if 0
        while (!st.empty() && edges[st.top()].empty()) {
            path.push_back(st.top());
            st.pop();
        }
        if (!st.empty()) {
            int u = st.top();
            int v = edges[u].front();
            edges[u].pop_front();
            st.push(v);
            dfs(edges, st, path);
        }
#endif
        st.push(u);
        if (!edges[u].empty()) {
            int v = edges[u].front();
            edges[u].pop_front();
            dfs(v, edges, st);
        }
    }
};
