#include "MaximalMatch.cpp"

#include <cppunit/extensions/HelperMacros.h>

class HungarianTest:public CppUnit::TestFixture {
public:
	void setUp() {}
	void tearDown() {}

	void testMaxMatch() {
		Hungarian hungarian(3, 4);
		int result = hungarian.maxMatch([](int u, int v){return false;});
		CPPUNIT_ASSERT(result == 0);

		result = hungarian.maxMatch(
			[](int u, int v){
					if ((u == 0 && (v == 0 || v == 2)) ||
						(u == 1 && v == 1) ||
						(u == 2 && (v == 0 || v ==2 || v == 3))) {
						return true;
					}
					return false;
				}
			);
		CPPUNIT_ASSERT(result == 3);

	}

	CPPUNIT_TEST_SUITE(HungarianTest);
	CPPUNIT_TEST(testMaxMatch);
	CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(HungarianTest);
