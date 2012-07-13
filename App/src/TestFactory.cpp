#include "TestFactory.h"
#include "TestRoughness.h"
#include "TestFresnelCoeff.h"
#include "TestFormFactor.h"
#include "TestDiffuseReflection.h"
#include "TestIsGISAXS1.h"
#include "TestIsGISAXS3.h"
#include "TestIsGISAXS9.h"
#include "TestIsGISAXS10.h"
#include "TestConvolution.h"
#include "TestDetectorResolution.h"
#include "TestMesoCrystal.h"

#include "TBenchmark.h"



TestFactory::TestFactory() : m_benchmark(0)
{
    setOwnObjects(true);

    registerItem("roughness",   IFactoryCreateFunction<TestRoughness, IFunctionalTest> );
    registerItem("fresnel",     IFactoryCreateFunction<TestFresnelCoeff, IFunctionalTest> );
    registerItem("formfactor",  IFactoryCreateFunction<TestFormFactor, IFunctionalTest> );
    registerItem("diffuse",     IFactoryCreateFunction<TestDiffuseReflection, IFunctionalTest> );
    registerItem("isgisaxs1",   IFactoryCreateFunction<TestIsGISAXS1, IFunctionalTest> );
    registerItem("isgisaxs3",   IFactoryCreateFunction<TestIsGISAXS3, IFunctionalTest> );
    registerItem("isgisaxs9",   IFactoryCreateFunction<TestIsGISAXS9, IFunctionalTest> );
    registerItem("isgisaxs10",  IFactoryCreateFunction<TestIsGISAXS10, IFunctionalTest> );
    registerItem("convolution", IFactoryCreateFunction<TestConvolution, IFunctionalTest> );
    registerItem("detectorresolution", IFactoryCreateFunction<TestDetectorResolution, IFunctionalTest> );
    registerItem("mesocrystal", IFactoryCreateFunction<TestMesoCrystal, IFunctionalTest> );

    m_benchmark = new TBenchmark();
}


TestFactory::~TestFactory()
{
    delete m_benchmark;
}


/* ************************************************************************* */
// print benchmark summary on the screen
/* ************************************************************************* */
void TestFactory::print_benchmarks()
{
    std::cout << "--- TestFactory::print_benchmarks() ---" << std::endl;
    float_t rp, cp;
    m_benchmark->Summary(rp, cp);
}


/* ************************************************************************* */
// execute specific functional tests
/* ************************************************************************* */
void TestFactory::execute(std::string name)
{
    //IFunctionalTest *test = TestFactory::instance().createItem( args[i] );
    IFunctionalTest *test(0);
    try {
        test = createItem( name );
    } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
        std::cout << "TestFactory::execute() -> Warning. No test with name '" << name << "' is defined." << std::endl;
        return;
    }

    test->initialise();
    m_benchmark->Start(name.c_str());
    test->execute();
    m_benchmark->Stop(name.c_str());
    m_benchmark->Show(name.c_str());
    test->finalise();

}


void TestFactory::profile(std::string name)
{
    //IFunctionalTest *test = TestFactory::instance().createItem( args[i] );
    IFunctionalTest *test(0);
    try {
        test = createItem( name );
    } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
        std::cout << "TestFactory::execute() -> Warning. No test with name '" << name << "' is defined." << std::endl;
        return;
    }

    test->initialise();
    for(int i=0; i<10; i++) test->execute();

}



/* ************************************************************************* */
// execute all registered functional tests
/* ************************************************************************* */
void TestFactory::execute_all()
{
    CallbackMap_t::const_iterator it;
    for(it=m_callbacks.begin(); it != m_callbacks.end(); it++ ) {
        execute( it->first );
        //createItem( it->first )->execute();
    }
    print_benchmarks();
}


/* ************************************************************************* */
// print on the screen names of registered tests
/* ************************************************************************* */
void TestFactory::print_testnames()
{
    std::string help;
    help += "TestFactory::print_testnames() -> Info. \n";
    help += "You can run few functional tests by running './App testname'\n";
    help += "List of available tests are below:";
    std::cout << help << std::endl;
    CallbackMap_t::const_iterator it;
    for(it=m_callbacks.begin(); it != m_callbacks.end(); it++ ) {
        std::cout << it->first << std::endl;
    }
}


/* ************************************************************************* */
// return vector of registered test names
/* ************************************************************************* */
std::vector<std::string > TestFactory::get_testnames()
{
    std::vector<std::string > names;
    CallbackMap_t::const_iterator it;
    for(it=m_callbacks.begin(); it != m_callbacks.end(); it++ ) {
        names.push_back(it->first);
    }

    return names;
}

