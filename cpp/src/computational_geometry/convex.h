
class Convex {
 public:
  struct Point {
    int x, y;

    bool operator < (const Point& other) const {
      return x < other.x || (x == other.x && y < other.y);
    }

    bool operator == (const Point& other) const {
      return x == other.x && y == other.y;
    }

    friend Point operator - (const Point& p1, const Point& p2) {
      return Point{p1.x-p2.x, p1.y-p2.y};
    }

    friend int64_t operator * (const Point& p1, const Point& p2) {
      return 1LL*p1.x*p2.y - 1LL*p1.y*p2.x;
    }

    friend int64_t dot_product(const Point& p1, const Point& p2) {
      return 1LL*p1.x*p2.x + 1LL*p1.y*p2.y;
    }
  };

  Convex(int cap): cap_(cap), n_(0) {
    alloc();
  }

  ~Convex() {
    dealloc();
  }

  void push(const Point& x) {
    while (n_ >= 2 && (pts_[n_-1]-pts_[n_-2])*(x-pts_[n_-1]) <= 0) n_--;
    pts_[n_++] = x;
  }

  static Convex merge(const Convex& q1, const Convex& q2) {
    Convex c(q1.n_ + q2.n_);

    int h1 = 0, h2 = 0;
    while (h1 < q1.n_ && h2 < q2.n_) {
      if (q1.pts_[h1] < q2.pts_[h2]) {
        c.push(q1.pts_[h1++]);
      } else {
        c.push(q2.pts_[h2++]);
      }
    }
    while (h1 < q1.n_) {
      c.push(q1.pts_[h1++]);
    }
    while (h2 < q2.n_) {
      c.push(q2.pts_[h2++]);
    }
    return c;
  }

 private:
  Point* pts_;
  int cap_;
  int n_;

  void alloc() {
    pts_ = new Point[cap_];
  }

  void dealloc() {
    delete[] pts_;
  }

  friend class ConvexTest;
};
