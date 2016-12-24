#include <bits/stdc++.h>
using namespace std;

#include "TarjanSCC.h"

#include <boost/assign/list_of.hpp>
#include <cppunit/extensions/HelperMacros.h>

using namespace boost::assign;

class TarjanSCCTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testScc() {
        TarjanSCC::Graph g(8);
        g.add(0, 1);
        g.add(1, 2);
        g.add(1, 6);
        g.add(6, 2);
        g.add(0, 3);
        g.add(3, 4);
        g.add(4, 5);
        g.add(5, 7);
        g.add(5, 3);
        g.add(7, 3);

        TarjanSCC tarjan(g);
        tarjan.dfs();
        tarjan.assign();

        CPPUNIT_ASSERT(tarjan.belong == list_of(4)(3)(1)(0)(0)(0)(2)(0));

        CPPUNIT_ASSERT(tarjan.bcc[0] == list_of(7)(5)(4)(3));
        CPPUNIT_ASSERT(tarjan.bcc[1] == list_of(2));
        CPPUNIT_ASSERT(tarjan.bcc[2] == list_of(6));
        CPPUNIT_ASSERT(tarjan.bcc[3] == list_of(1));
        CPPUNIT_ASSERT(tarjan.bcc[4] == list_of(0));

        CPPUNIT_ASSERT(tarjan.ng[0].empty());
        CPPUNIT_ASSERT(tarjan.ng[1].empty());
        CPPUNIT_ASSERT(tarjan.ng[2] == list_of(1));
        CPPUNIT_ASSERT(tarjan.ng[3] == list_of(1)(2));
        CPPUNIT_ASSERT(tarjan.ng[4] == list_of(3)(0));

        CPPUNIT_ASSERT(tarjan.du == list_of(1)(2)(1)(1)(0));
    }

    CPPUNIT_TEST_SUITE(TarjanSCCTest);
    CPPUNIT_TEST(testScc);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(TarjanSCCTest);
