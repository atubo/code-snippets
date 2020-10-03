
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

  class Locator {
    int nowx;
    struct Query {
      int id;
      Point pt;
      bool operator < (const Query& other) const {
        return pt.x < other.pt.x;
      }
    };

    struct KeyPoint {
      int id;
      Point pt;
      bool operator < (const KeyPoint& other) const {
        if (pt.x == other.pt.x) {
          return id < other.id;
        }
        return pt.x < other.pt.x;
      }
    };

    struct Info {
      const Locator& locator;
      int id;
      double k;
      int x, y;
      Info(const Locator& loc, int id0,
          const Point& a, const Point& b)
          : locator(loc), id(id0), x(a.x), y(a.y) {
        k = 1.0 * (a.y - b.y) / (a.x - b.x);
      }

      bool operator < (const Info& other) const {
        constexpr double EPS = 1e-8;
        double y0 = k * (locator.nowx - x) + y;
        double y1 = other.k * (locator.nowx - other.x) + other.y;
        if (fabs(y1 - y0) > EPS) return y0 < y1;
        return k < other.k;
      }
    };

    const PlanarDualGraph& pdg_;
    using Iter = set<Info>::iterator;
    Query* queries_;
    KeyPoint* keyPoints_;
    set<Info> s_;
    Iter* it_;
    int* region_;
    int m_, q_;
    int kptid_ = 0;
    int qid_ = 0;

    void alloc() {
      queries_ = new Query[q_]{};
      keyPoints_ = new KeyPoint[2*m_]{};
      it_ = new Iter[2*m_]{};
      region_ = new int[q_]{};
    }

    void dealloc() {
      delete[] queries_;
      delete[] keyPoints_;
      delete[] it_;
      delete[] region_;
    }

   public:
    Locator(const PlanarDualGraph& pdg, int q) : pdg_(pdg), q_(q) {
      m_ = pdg_.m_;
      alloc();
    }

    ~Locator() {
      dealloc();
    }

    void addQuery(int x, int y) {
      queries_[qid_] = Query{qid_, Point(x, y)};
      qid_++;
    }

    void build() {
      for (int i = 0; i < m_; i++) {
        int eid = 2*i;
        int u = pdg_.edges_[eid].u;
        int v = pdg_.edges_[eid].v;
        if (pdg_.points_[u].x > pdg_.points_[v].x) {
          eid |= 1;
          swap(u, v);
        }

        if (pdg_.points_[u].x != pdg_.points_[v].x) {
          keyPoints_[kptid_].id = eid + 1;
          keyPoints_[kptid_++].pt = pdg_.points_[u];
          keyPoints_[kptid_].id = -(eid + 1);
          keyPoints_[kptid_++].pt = pdg_.points_[v];
        }
      }

      sort(keyPoints_, keyPoints_ + kptid_);
      sort(queries_, queries_ + q_);

      for (int i = 0, j = 0; i < q_; i++) {
        for (; j < kptid_ && keyPoints_[j].pt.x <= queries_[i].pt.x; j++) {
          nowx = keyPoints_[j].pt.x;
          int id = keyPoints_[j].id;
          if (id < 0) {
            s_.erase(it_[-id-1]);
          } else {
            id--;
            int u = pdg_.edges_[id].u;
            int v = pdg_.edges_[id].v;
            it_[id] = s_.insert(
                Info(*this, id, pdg_.points_[u], pdg_.points_[v])).first;
          }
        }
        nowx = queries_[i].pt.x;
        Point a = queries_[i].pt, b = a;
        b.x += 1;
        Iter pos = s_.lower_bound(Info(*this, 0, a, b));
        if (pos == s_.end()) region_[queries_[i].id] = pdg_.outerRegion_;
        else region_[queries_[i].id] = pdg_.enclose_[pos->id ^ 1];
      }
    }
    friend class PlanarDualGraphTest;
  };

  friend class PlanarDualGraphTest;
};
