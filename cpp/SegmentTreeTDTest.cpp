#include "SegmentTreeTDTest.h"
#include "SegmentTreeTD.cpp"

CPPUNIT_TEST_SUITE_REGISTRATION(SegmentTreeTDTest);

void SegmentTreeTDTest::test1()
{
    int64_t a[] = {1, 2, 3, 4};
    SegmentTreeTD tree(4, a);
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
    int64_t a[3] = {0};
    SegmentTreeTD tree(3, a);
    tree.update(0, 0, -1);
    tree.update(0, 0, 1);
    for (int i = 0; i < 3; i++) {
        int x = tree.query(i, i);
        CPPUNIT_ASSERT_EQUAL(0, x);
    }
}

void SegmentTreeTDTest::test3()
{
    int64_t a[3] = {-2, -2, -2};
    SegmentTreeTD tree(3, a);
    tree.update(0, 2, 2);
    tree.update(2, 2, -1);
    int x = tree.query(0, 2);
    CPPUNIT_ASSERT_EQUAL(-1, x);
}
