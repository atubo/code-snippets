#include <bits/stdc++.h>

using namespace std;

#include "geometry/convex.h"

#include <cppunit/extensions/HelperMacros.h>

class ConvexTest : public CppUnit::TestFixture {
  using Point = Convex::Point;
 public:
  void setUp() {}
  void tearDown() {}

  void testPush() {
    Convex convex(5);
    convex.push(Point{0, 0});
    convex.push(Point{1, 1});
    convex.push(Point{2, 0});
    convex.push(Point{3, 1});
    convex.push(Point{4, 3});

    CPPUNIT_ASSERT(convex.n_ == 4);
    CPPUNIT_ASSERT(convex.pts_[0] == Point({0, 0}));
    CPPUNIT_ASSERT(convex.pts_[1] == Point({2, 0}));
    CPPUNIT_ASSERT(convex.pts_[2] == Point({3, 1}));
    CPPUNIT_ASSERT(convex.pts_[3] == Point({4, 3}));
  }

  void testConstructor() {
    vector<Point> pts;
    pts.push_back(Point{0, 0});
    pts.push_back(Point{0, -1});
    pts.push_back(Point{0, 2});
    pts.push_back(Point{1, -2});
    pts.push_back(Point{-1, -2});
    pts.push_back(Point{2, 2});
    pts.push_back(Point{2, 0});
    pts.push_back(Point{-2, 0});
    pts.push_back(Point{3, -1});
    pts.push_back(Point{-3, 1});

    Convex convex(std::move(pts));
    CPPUNIT_ASSERT_EQUAL(6, convex.n_);
    CPPUNIT_ASSERT(convex.pts_[0] == Point({-3, 1}));
    CPPUNIT_ASSERT(convex.pts_[1] == Point({-1, -2}));
    CPPUNIT_ASSERT(convex.pts_[2] == Point({1, -2}));
    CPPUNIT_ASSERT(convex.pts_[3] == Point({3, -1}));
    CPPUNIT_ASSERT(convex.pts_[4] == Point({2, 2}));
    CPPUNIT_ASSERT(convex.pts_[5] == Point({0, 2}));
  }

  void testMerge() {
    Convex c1(5);
    c1.push(Point{0, 1});
    c1.push(Point{1, -1});
    c1.push(Point{2, -1});
    c1.push(Point{4, 0});
    c1.push(Point{6, 2});

    Convex c2(5);
    c2.push(Point{1, 0});
    c2.push(Point{2, -2});
    c2.push(Point{3, -2});
    c2.push(Point{4, 0});
    c2.push(Point{5, 3});

    auto c = Convex::merge(c1, c2);
    CPPUNIT_ASSERT(c.n_ == 5);
    CPPUNIT_ASSERT(c.pts_[0] == Point({0, 1}));
    CPPUNIT_ASSERT(c.pts_[1] == Point({1, -1}));
    CPPUNIT_ASSERT(c.pts_[2] == Point({2, -2}));
    CPPUNIT_ASSERT(c.pts_[3] == Point({3, -2}));
    CPPUNIT_ASSERT(c.pts_[4] == Point({6, 2}));
  }

  CPPUNIT_TEST_SUITE(ConvexTest);
  CPPUNIT_TEST(testPush);
  CPPUNIT_TEST(testConstructor);
  CPPUNIT_TEST(testMerge);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ConvexTest);
