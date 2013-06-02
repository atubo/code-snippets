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
