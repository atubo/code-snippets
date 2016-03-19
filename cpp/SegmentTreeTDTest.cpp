#include "SegmentTreeTDTest.h"
#include "SegmentTreeTD.cpp"

#include <cassert>

CPPUNIT_TEST_SUITE_REGISTRATION(SegmentTreeTDTest);


const int MAXINT = numeric_limits<int>::max();


void SegmentTreeTDTest::test1()
{
    int a[] = {1, 2, 3, 4};
    auto combine = [](int x, int y) {return min(x, y);};
    auto accu = [](int x, int y) {return x+y;};
    auto apply = [](int x, int y, int) {return x+y;};

    SegmentTreeTD<int> tree(4, a, MAXINT, combine, accu, apply);
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
    int a[3] = {0, 0, 0};
    auto combine = [](int x, int y) {return min(x, y);};
    auto accu = [](int x, int y) {return x+y;};
    auto apply = [](int x, int y, int) {return x+y;};

    SegmentTreeTD<int> tree(3, a, MAXINT, combine, accu, apply);
    tree.update(0, 0, -1);
    tree.update(0, 0, 1);
    for (int i = 0; i < 3; i++) {
        int x = tree.query(i, i);
        CPPUNIT_ASSERT_EQUAL(0, x);
    }
}

void SegmentTreeTDTest::test3()
{
    int a[3] = {-2, -2, -2};
    auto combine = [](int x, int y) {return min(x, y);};
    auto accu = [](int x, int y) {return x+y;};
    auto apply = [](int x, int y, int) {return x+y;};

    SegmentTreeTD<int> tree(3, a, MAXINT, combine, accu, apply);
    tree.update(0, 2, 2);
    tree.update(2, 2, -1);
    int x = tree.query(0, 2);
    CPPUNIT_ASSERT_EQUAL(-1, x);
}

void SegmentTreeTDTest::testRangeSum()
{
    int a[5] = {0, 1, 2, 3, 4};
    auto add = [](int x, int y) {return x+y;};
    auto apply = [](int x, int d, int count) {return x + d*count;};

    SegmentTreeTD<int> tree(5, a, 0, add, add, apply);
    CPPUNIT_ASSERT_EQUAL(10, tree.query(0, 4));

    tree.update(1, 3, -2);
    CPPUNIT_ASSERT_EQUAL(4, tree.query(0, 4));
    CPPUNIT_ASSERT_EQUAL(0, tree.query(1, 3));
    CPPUNIT_ASSERT_EQUAL(-1, tree.query(1, 2));
}
