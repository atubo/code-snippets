#ifndef SEGMENTTREETDTEST_H
#define SEGMENTTREETDTEST_H

#include <cppunit/extensions/HelperMacros.h>

class SegmentTreeTDTest:public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(SegmentTreeTDTest);
    CPPUNIT_TEST(test1);
    CPPUNIT_TEST(test2);
    CPPUNIT_TEST(test3);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp() {}
    void tearDown() {}
    void test1();
    void test2();
    void test3();
};

#endif
