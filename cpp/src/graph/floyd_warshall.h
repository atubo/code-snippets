class FloydWarshall {
public:
    FloydWarshall(const vector<vector<int64_t> >& graph)
        :dist_(graph)
    {
        int V = dist_.size();

        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist_[i][k] + dist_[k][j] < dist_[i][j]) {
                        dist_[i][j] = dist_[i][k] + dist_[k][j];
                    }
                }
            }
        }
    }

    vector<vector<int64_t> > dist_;
};
