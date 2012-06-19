#include "TestFactory.h"
#include "TestRoughness.h"
#include "TestFresnelCoeff.h"
#include "TestFormFactor.h"
#include "TestDWBAFormFactor.h"
#include "TestDiffuseReflection.h"
#include "TestIsGISAXS10.h"
#include "TestConvolution.h"

#include "TBenchmark.h"



TestFactory::TestFactory() : m_benchmark(0)
{
    setOwnObjects(true);

    registerItem("roughness",  IFactoryCreateFunction<TestRoughness, IFunctionalTest> );
    registerItem("fresnel",    IFactoryCreateFunction<TestFresnelCoeff, IFunctionalTest> );
    registerItem("formfactor", IFactoryCreateFunction<TestFormFactor, IFunctionalTest> );
    registerItem("dwba",       IFactoryCreateFunction<TestDWBAFormFactor, IFunctionalTest> );
    registerItem("diffuse",    IFactoryCreateFunction<TestDiffuseReflection, IFunctionalTest> );
    registerItem("isgisaxs10", IFactoryCreateFunction<TestIsGISAXS10, IFunctionalTest> );
    registerItem("convolution", IFactoryCreateFunction<TestConvolution, IFunctionalTest> );

    m_benchmark = new TBenchmark();
}


TestFactory::~TestFactory()
{
    print_benchmarks();
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

    m_benchmark->Start(name.c_str());
    test->execute();
    m_benchmark->Stop(name.c_str());
    m_benchmark->Show(name.c_str());

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
}

