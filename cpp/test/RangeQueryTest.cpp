#include "RangeQuery.cpp"

#include <cppunit/extensions/HelperMacros.h>

class RangeQueryTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}
    
    void testQuery() {
        RangeQuery<int> rq;
        rq.put(1);
        rq.put(2);
        rq.put(4);
        rq.put(5);

        CPPUNIT_ASSERT(!rq.hasElementIn(-1, 0));
        CPPUNIT_ASSERT(!rq.hasElementIn(0, 0));
        CPPUNIT_ASSERT(!rq.hasElementIn(0, 1));
        CPPUNIT_ASSERT(!rq.hasElementIn(5, 5));
        CPPUNIT_ASSERT(!rq.hasElementIn(6, 10));

        CPPUNIT_ASSERT(rq.hasElementIn(0, 2));
        CPPUNIT_ASSERT(rq.hasElementIn(2, 4));
        CPPUNIT_ASSERT(rq.hasElementIn(2, 5));
        CPPUNIT_ASSERT(rq.hasElementIn(3, 5));
    }

    CPPUNIT_TEST_SUITE(RangeQueryTest);
    CPPUNIT_TEST(testQuery);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(RangeQueryTest);

