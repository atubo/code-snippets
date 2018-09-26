#include <bits/stdc++.h>

using namespace std;

#include "math/gaussian_elimination.h"

#include <cppunit/extensions/HelperMacros.h>

class GaussianEliminationTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testSolve() {
        GaussianElimination gauss(5);
        double A[5][5] = {
            {2.0, -1.0, 4.0, -3.0, 1.0},
            {-1.0, 1.0, 2.0, 1.0, 3.0},
            {4.0, 2.0, 3.0, 3.0, -1.0},
            {-3.0, 1.0, 3.0, 2.0, 4.0},
            {1.0, 3.0, 1.0, 4.0, 4.0}
        };
        double X[5] = {11.0, 14.0, 4.0, 16.0, 18.0};
        for (int i = 0; i < 5; i++) {
            gauss.X[i] = X[i];
            for (int j = 0; j < 5; j++) {
                gauss.A[i][j] = A[i][j];
            }
        }
        gauss.solve();
        double expected[5] = {
            0.037037,
            4.666667,
            1.444444,
            -2.296296,
            2.925926
        };
        for (int i = 0; i < 5; i++) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[i], gauss.X[i], 1e-6);
        }
    }

    CPPUNIT_TEST_SUITE(GaussianEliminationTest);
    CPPUNIT_TEST(testSolve);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(GaussianEliminationTest);
