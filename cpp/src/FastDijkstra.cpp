class FastDijkstra {
 public:
  static const int64_t INF;

  typedef pair<int64_t,int> PII;  // pair = (dist, vertex)

  FastDijkstra(int N_): N(N_), edges(N), dist(N, INF), dad(N, -1) {}

  void addEdge(int u, int v, int64_t wt) {
    edges[u].push_back(make_pair(wt, v));
  }

  const vector<int64_t>& getDist() const {
    return dist;
  }

  const vector<int>& getDad() const {
    return dad;
  }

  void solve(int s) {
    // use priority queue in which top element has the "smallest" priority
    priority_queue<PII, vector<PII>, greater<PII> > Q;
    Q.push (make_pair (0, s));
    dist[s] = 0;
    while (!Q.empty()){
      PII p = Q.top();
      // break here if we want to stop when we find a target node
      Q.pop();

      int here = p.second;
      for (vector<PII>::const_iterator it=edges[here].begin();
          it!=edges[here].end(); it++){
        if (dist[here] + it->first < dist[it->second]){
          dist[it->second] = dist[here] + it->first;
          dad[it->second] = here;
          Q.push (make_pair (dist[it->second], it->second));
        }
      }
    }
  }

  void reset() {
    dist.assign(N, INF);
    dad.assign(N, -1);
  }

 private:
  const int N;
  vector<vector<PII>> edges;
  vector<int64_t> dist;
  vector<int> dad;
};

const int64_t FastDijkstra::INF = 0x7FFFFFFFFFFFFFFF;
