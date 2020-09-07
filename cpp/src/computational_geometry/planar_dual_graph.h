
const double PI = acos(-1);

class PlanarDualGraph {
  struct Point {
    Point(int xx = 0, int yy = 0) : x(xx), y(yy) {}
    int x, y;

    Point operator - (const Point& other) const {
      return Point(x - other.x, y - other.y);
    }

    friend int64_t cross(const Point& a, const Point& b) {
      return 1LL * a.x * b.y - 1LL * a.y * b.x;
    }
  };

  struct Edge {
    int id;
    int u, v;
    double angle;
    Edge(int idd = -1, int uu = 0, int vv = 0, double agl = 0) :
      id(idd), u(uu), v(vv), angle(agl) {
        if (angle < 0) {
          angle += 2.0 * PI;
        }
      }
  };

 public:
  PlanarDualGraph(int n, int m) : n_(n), m_(m) {
    alloc();
  }

  ~PlanarDualGraph() {
    dealloc();
  }

  void addEdge(int u, int v) {
    Point z = points_[v] - points_[u];
    edges_[eid_] = Edge{eid_, u, v, atan2(z.y, z.x)};
    eid_++;
    edges_[eid_] = Edge{eid_, v, u, atan2(-z.y, -z.x)};
    eid_++;
  }

  void addPoint(int x, int y) {
    points_[pid_++] = {x, y};
  }

  void build() {
    vector<pair<double, int>> tmp;
    for (int i = 0; i < 2*m_; i++) {
      tmp.push_back(make_pair(edges_[i].angle, i));
    }
    sort(tmp.begin(), tmp.end());
    for (int i = 0; i < 2*m_; i++) {
      int eid = tmp[i].second;
      Edge e = edges_[eid];
      rank_[eid] = eout_[e.u].size();
      eout_[e.u].push_back(eid);
    }

    for (int i = 0; i < n_; i++) {
      for (int j = 0; j < (int)eout_[i].size(); j++) {
        findRegion(i, eout_[i][j]);
      }
    }
  }

 private:
  int n_, m_;
  Point* points_;
  int pid_ = 0;
  Edge* edges_;
  int eid_ = 0;
  bool* vis_;
  int* rank_;
  int* enclose_;  // edge -> region
  vector<int> *eout_;
  int rid_ = 0;
  int outerRegion_ = -1;
  int64_t* areas_;

  void alloc() {
    points_ = new Point[n_]{};
    edges_ = new Edge[2*m_]{};
    vis_ = new bool[2*m_]{};
    rank_ = new int[2*m_]{};
    enclose_ = new int[2*m_]{};
    eout_ = new vector<int>[n_]{};
    areas_ = new int64_t[m_]{};
  }

  void dealloc() {
    delete[] points_;
    delete[] edges_;
    delete[] vis_;
    delete[] rank_;
    delete[] enclose_;
    delete[] eout_;
    delete[] areas_;
  }

  void findRegion(int x, int eid) {
    if (vis_[eid]) return;
    int64_t area = 0;
    while (!vis_[eid]) {
      area += cross(points_[x], points_[edges_[eid].v]);
      vis_[eid] = true;
      enclose_[eid] = rid_;
      x = edges_[eid].v;
      if (!rank_[eid ^ 1]) eid = eout_[x].back();
      else eid = eout_[x][rank_[eid ^ 1] - 1];
    }
    if (area < 0) outerRegion_ = rid_;
    areas_[rid_] = area;
    rid_++;
  }

  friend class PlanarDualGraphTest;
};
