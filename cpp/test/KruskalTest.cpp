#include <bits/stdc++.h>

using namespace std;

#include "Kruskal.h"

#include <boost/assign/list_of.hpp>
#include <cppunit/extensions/HelperMacros.h>

using namespace boost::assign;

class KruskalTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testKruskal() {
        using TIII = tuple<int, int, int>;
        vector<TIII> edges  { TIII(2, 0, 1), TIII(2, 0, 2), TIII(1, 0, 3),
                               TIII(1, 1, 2), TIII(1, 1, 3),
                               TIII(2, 2, 3) };
        auto adj = Kruskal::mst(edges, 4);
        CPPUNIT_ASSERT(adj[0] == list_of(3));
        CPPUNIT_ASSERT(adj[1] == list_of(2)(3));
        CPPUNIT_ASSERT(adj[2] == list_of(1));
        CPPUNIT_ASSERT(adj[3] == list_of(0)(1));
    }

    CPPUNIT_TEST_SUITE(KruskalTest);
    CPPUNIT_TEST(testKruskal);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(KruskalTest);
