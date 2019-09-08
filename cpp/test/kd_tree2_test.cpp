#include <bits/stdc++.h>

using namespace std;

#include "data_structures/kd_tree2.h"

#include <cppunit/extensions/HelperMacros.h>

class KdTree2Test:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        KdTree2 kd(4);
        kd.pt[1] = {0, 0};
        kd.pt[2] = {1, -1};
        kd.pt[3] = {2, 2};
        kd.pt[4] = {3, -3};
        kd.build(1, 4);
        auto p = kd.point(1);
        CPPUNIT_ASSERT(p.x[0] == 1 && p.x[1] == -1);
        pair<int, int> r = kd.rangex(1);
        CPPUNIT_ASSERT(r == make_pair(0, 3));
        r = kd.rangey(1);
        CPPUNIT_ASSERT(r == make_pair(-3, 2));
        int c = kd.leftChild(1);
        r = kd.rangex(c);
        CPPUNIT_ASSERT(r == make_pair(3, 3));
        c = kd.rightChild(1);
        r = kd.rangex(c);
        CPPUNIT_ASSERT(r == make_pair(0, 2));
        r = kd.rangey(c);
        CPPUNIT_ASSERT(r == make_pair(0, 2));
    }

    CPPUNIT_TEST_SUITE(KdTree2Test);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(KdTree2Test);

