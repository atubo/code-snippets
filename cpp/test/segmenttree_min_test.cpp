#include <bits/stdc++.h>

using namespace std;

#include "data_structures/segmenttree_min.h"

#include <cppunit/extensions/HelperMacros.h>

class SegmentTreeMinTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        SegmentTreeMin st(4);
        st.update(-1, 1, 3);
        st.update(-2, 2, 3);
        auto ret = st.query(1, 4);
        CPPUNIT_ASSERT(check(ret, -3, 2));

        ret = st.query(3, 4);
        CPPUNIT_ASSERT(check(ret, -3, 3));

        st.update(-2, 1, 1);
        ret = st.query(1, 4);
        CPPUNIT_ASSERT(check(ret, -3, 1));

        st.update(-1, 1, 1);
        ret = st.query(1, 4);
        CPPUNIT_ASSERT(check(ret, -4, 1));

        ret = st.query(2, 4);
        CPPUNIT_ASSERT(check(ret, -3, 2));
    }

private:
    bool check(const SegmentTreeMin::QueryResult &qr,
               int64_t value, int pos) {
        return qr.value == value && qr.pos == pos;
    }

    CPPUNIT_TEST_SUITE(SegmentTreeMinTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SegmentTreeMinTest);
