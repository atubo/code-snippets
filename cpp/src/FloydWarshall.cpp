#include <vector>
using namespace std;

class FloydWarshall {
public:
    FloydWarshall(const vector<vector<int> >& graph)
        :m_graph(graph), m_dist(graph)
    {
        int V = m_graph.size();

        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (m_dist[i][k] + m_dist[k][j] < m_dist[i][j]) {
                        m_dist[i][j] = m_dist[i][k] + m_dist[k][j];
                    }
                }
            }
        }
    }

    const vector<vector<int> > getDist() const {
        return m_dist;
    }
private:
    vector<vector<int> > m_graph;
    vector<vector<int> > m_dist;
};
