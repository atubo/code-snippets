#include <cppunit/ui/text/TestRunner.h>
#include "SegmentTreeTDTest.h"
#include "SegmentTreeMinTest.h"

int main()
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = 
        CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    runner.run();

    return 0;
}
