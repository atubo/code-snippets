#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

int main()
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = 
        CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    runner.run();

    return 0;
}
