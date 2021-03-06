#include <bits/stdc++.h>
#include <cppunit/extensions/HelperMacros.h>
using namespace std;

#include "SegmentTreeTD.h"

class SegmentTreeTDTest:public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(SegmentTreeTDTest);
    CPPUNIT_TEST(test1);
    CPPUNIT_TEST(test2);
    CPPUNIT_TEST(test3);
    CPPUNIT_TEST(testRangeSum1);
    CPPUNIT_TEST(testRangeSum2);
    CPPUNIT_TEST(testRangeSet);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp() {}
    void tearDown() {}
    void test1();
    void test2();
    void test3();
    void testRangeSum1();
    void testRangeSum2();
    void testRangeSet();
};


CPPUNIT_TEST_SUITE_REGISTRATION(SegmentTreeTDTest);


const int MAXINT = numeric_limits<int>::max();


void SegmentTreeTDTest::test1()
{
    vector<int> a = {1, 2, 3, 4};
    auto combine = [](int x, int y) {return min(x, y);};
    auto accu = [](int x, int y) {return x+y;};
    auto apply = [](int x, int y, int) {return x+y;};

    SegmentTreeTD<int> tree(a, MAXINT, 0, combine, accu, apply);
    tree.update(3, 3, -1);
    tree.update(0, 0, -1);
    int x = tree.query(0, 0);
    CPPUNIT_ASSERT_EQUAL(0, x);

    x = tree.query(3, 3);
    CPPUNIT_ASSERT_EQUAL(3, x);

    x = tree.query(0, 1);
    CPPUNIT_ASSERT_EQUAL(0, x);

    x = tree.query(2, 3);
    CPPUNIT_ASSERT_EQUAL(3, x);
}

void SegmentTreeTDTest::test2()
{
    vector<int> a = {0, 0, 0};
    auto combine = [](int x, int y) {return min(x, y);};
    auto accu = [](int x, int y) {return x+y;};
    auto apply = [](int x, int y, int) {return x+y;};

    SegmentTreeTD<int> tree(a, MAXINT, 0, combine, accu, apply);
    tree.update(0, 0, -1);
    tree.update(0, 0, 1);
    for (int i = 0; i < 3; i++) {
        int x = tree.query(i, i);
        CPPUNIT_ASSERT_EQUAL(0, x);
    }
}

void SegmentTreeTDTest::test3()
{
    vector<int> a = {-2, -2, -2};
    auto combine = [](int x, int y) {return min(x, y);};
    auto accu = [](int x, int y) {return x+y;};
    auto apply = [](int x, int y, int) {return x+y;};

    SegmentTreeTD<int> tree(a, MAXINT, 0, combine, accu, apply);
    tree.update(0, 2, 2);
    tree.update(2, 2, -1);
    int x = tree.query(0, 2);
    CPPUNIT_ASSERT_EQUAL(-1, x);
}

void SegmentTreeTDTest::testRangeSum1()
{
    vector<int> a = {0, 1, 2, 3, 4};
    auto add = [](int x, int y) {return x+y;};
    auto apply = [](int x, int d, int count) {return x + d*count;};

    SegmentTreeTD<int> tree(a, 0, 0, add, add, apply);
    CPPUNIT_ASSERT_EQUAL(10, tree.query(0, 4));

    tree.update(1, 3, -2);
    CPPUNIT_ASSERT_EQUAL(4, tree.query(0, 4));
    CPPUNIT_ASSERT_EQUAL(0, tree.query(1, 3));
    CPPUNIT_ASSERT_EQUAL(-1, tree.query(1, 2));
}

void SegmentTreeTDTest::testRangeSum2()
{
    vector<int> a = {1, 1, 1, 1, 1, 0};
    auto add = [](int x, int y) {return x+y;};
    auto apply = [](int x, int d, int count) {return x + d*count;};

    SegmentTreeTD<int> tree(a, 0, 0, add, add, apply);

    tree.update(0, 4, -1);
    CPPUNIT_ASSERT_EQUAL(0, tree.query(1, 1));
    tree.update(5, 5, 1);
    CPPUNIT_ASSERT_EQUAL(1, tree.query(2, 5));
}

void SegmentTreeTDTest::testRangeSet()
{
    vector<int> a = {0, 0, 0, 0, 0};
    auto add = [](int x, int y) {return x+y;};
    auto accu = [](int x, int y) {return x;};
    auto apply = [](int x, int d, int count) {
        return d == INT_MIN ? x : d*count;
    };

    SegmentTreeTD<int> tree(a, 0, INT_MIN, add, accu, apply);

    tree.update(3, 4, 1);
    CPPUNIT_ASSERT_EQUAL(0, tree.query(0, 2));
    CPPUNIT_ASSERT_EQUAL(2, tree.query(3, 4));
    tree.update(3, 3, 1);
    CPPUNIT_ASSERT_EQUAL(0, tree.query(0, 2));
    CPPUNIT_ASSERT_EQUAL(2, tree.query(3, 4));
}
