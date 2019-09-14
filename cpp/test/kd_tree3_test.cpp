#include <bits/stdc++.h>

using namespace std;

#include "data_structures/kd_tree3.h"

#include <cppunit/extensions/HelperMacros.h>

class KdTree3Test:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        using Point = KdTree3<2>::Point;
        KdTree3<2> kd(11);
        kd.insert(Point{{0, 0}, 0});
        for (int i = 1; i <= 4; i++) {
            kd.insert(Point{{i, i}, i});
            kd.insert(Point{{-i, -i}, i});
        }
        CPPUNIT_ASSERT(verifyNode2d(kd, 1, 3, 2, 9, 0, 0, 4, 4, -4, -4, 4));
        for (int k = 2; k <= 8; k += 2) {
            int rc = (k < 8 ? k+2 : 0);
            bool ok = verifyNode2d(kd, k, 0, rc, 5-k/2, k/2, k/2, 4, 4,
                                   k/2, k/2, 4);
            CPPUNIT_ASSERT(ok);
        }

        for (int k = 3; k <= 9; k += 2) {
            int lc = (k < 9 ? k+2 : 0);
            int x = k/2;
            bool ok = verifyNode2d(kd, k, lc, 0, 5-k/2,
                                   -x, -x, -x, -x, -4, -4, 4);
            CPPUNIT_ASSERT(ok);
        }

        // add two, now it should rebalance
        kd.insert(Point{{5, 5}, 5});
        kd.insert(Point{{-5, -5}, 5});
        CPPUNIT_ASSERT(verifyNode2d(kd, 1, 3, 2, 11, 0, 0, 5, 5, -5, -5, 5));
        CPPUNIT_ASSERT(verifyNode2d(kd, 2, 4, 8, 5, 3, 3, 5, 5, 1, 1, 5));
        CPPUNIT_ASSERT(verifyNode2d(kd, 3, 5, 9, 5, -3, -3, -1, -1, -5, -5, 5));
        CPPUNIT_ASSERT(verifyNode2d(kd, 4, 0, 6, 2, 1, 1, 2, 2, 1, 1, 2));
        CPPUNIT_ASSERT(verifyNode2d(kd, 5, 0, 7, 2, -5, -5, -4, -4, -5, -5, 5));
        CPPUNIT_ASSERT(verifyNode2d(kd, 6, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2));
        CPPUNIT_ASSERT(verifyNode2d(kd, 7, 0, 0, 1, -4, -4, -4, -4, -4, -4, 4));
        CPPUNIT_ASSERT(verifyNode2d(kd, 8, 0, 10, 2, 4, 4, 5, 5, 4, 4, 5));
        CPPUNIT_ASSERT(verifyNode2d(kd, 9, 0, 11, 2, -2, -2, -1,-1, -2, -2, 2));
        CPPUNIT_ASSERT(verifyNode2d(kd, 10, 0, 0, 1, 5, 5, 5, 5, 5, 5, 5));
        CPPUNIT_ASSERT(verifyNode2d(kd, 11, 0, 0, 1, -1, -1, -1, -1, -1, -1, 1));
    }

    CPPUNIT_TEST_SUITE(KdTree3Test);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();

private:
    bool verifyNode2d(const KdTree3<2> &kd, int k, int lc, int rc,
                      int sz, int x, int y,
                      int maxx, int maxy, int minx, int miny, int maxw) {
        if (kd.lc_[k] != lc || kd.rc_[k] != rc) return false;
        if (kd.size_[k] != sz) return false;
        if (kd.d_[k].x[0] != x || kd.d_[k].x[1] != y) return false;
        if (kd.max_[0][k] != maxx || kd.max_[1][k] != maxy) return false;
        if (kd.min_[0][k] != minx || kd.min_[1][k] != miny) return false;
        return kd.maxwt_[k] == maxw;
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(KdTree3Test);
