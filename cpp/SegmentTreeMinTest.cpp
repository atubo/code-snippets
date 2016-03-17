#include "SegmentTreeMinTest.h"
#include "SegmentTreeMin.cpp"

CPPUNIT_TEST_SUITE_REGISTRATION(SegmentTreeMinTest);

void SegmentTreeMinTest::test1()
{
    SegmentTreeMin tree(4, 1000, [](int i, int j){return min(i, j);});
    tree.update(0, 4);
    tree.update(1, 2);
    tree.update(2, 3);
    tree.update(3, 1);

    CPPUNIT_ASSERT_EQUAL(1, tree.findMin(0, 3));
    CPPUNIT_ASSERT_EQUAL(2, tree.findMin(0, 2));
    CPPUNIT_ASSERT_EQUAL(1, tree.findMin(1, 3));
}

void SegmentTreeMinTest::test2()
{
    SegmentTreeMin tree(15, 1000, [](int i, int j){return i|j;});
    for (int i = 0; i < 15; i++) {
        tree.update(i, i+1);
    }

    CPPUNIT_ASSERT_EQUAL(15, tree.findMin(5, 9));
}
