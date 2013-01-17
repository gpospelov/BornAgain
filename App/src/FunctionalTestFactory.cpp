#include "FunctionalTestFactory.h"
#include "TestRoughness.h"
#include "TestFresnelCoeff.h"
#include "TestFormFactor.h"
#include "TestFumiliLMA.h"
#include "TestDiffuseReflection.h"
#include "TestIsGISAXS1.h"
#include "TestIsGISAXS2.h"
#include "TestIsGISAXS3.h"
#include "TestIsGISAXS4.h"
#include "TestIsGISAXS5.h"
#include "TestIsGISAXS7.h"
#include "TestIsGISAXS8.h"
#include "TestIsGISAXS9.h"
#include "TestIsGISAXS10.h"
#include "TestIsGISAXS11.h"
#include "TestIsGISAXS12.h"
#include "TestConvolution.h"
#include "TestDetectorResolution.h"
#include "TestMesoCrystal1.h"
#include "TestMesoCrystal2.h"
#include "TestRootTree.h"
#include "TestFittingModule1.h"
#include "TestFittingModule2.h"
#include "TestFittingModule3.h"
#include "TestPerformance.h"
#include "TestMultiLayerRoughness.h"
#include "TestMiscellaneous.h"
#include "TestFittingBenchmark.h"
#include "TestFourier.h"
#include "TestToyExperiment.h"


#include "TBenchmark.h"



FunctionalTestFactory::FunctionalTestFactory() : m_benchmark(0)
{
    setOwnObjects(true);

    registerItem("roughness",   IFactoryCreateFunction<TestRoughness, IFunctionalTest>,
                 "functional test: roughness parameters");
    registerItem("fresnel",     IFactoryCreateFunction<TestFresnelCoeff, IFunctionalTest>,
                 "functional test: fresnel coefficients calculations");
    registerItem("formfactor",  IFactoryCreateFunction<TestFormFactor, IFunctionalTest>,
                 "functional test: some formfactor");
    registerItem("diffuse",     IFactoryCreateFunction<TestDiffuseReflection, IFunctionalTest>,
                 "functional test: diffuse scattering from multi layer with roughness (obsolete)");
    registerItem("isgisaxs01",   IFactoryCreateFunction<TestIsGISAXS1, IFunctionalTest>,
                 "functional test: isgisaxs ex-1 (2 types of particles without inteference on top of substrate)");
    registerItem("isgisaxs02",   IFactoryCreateFunction<TestIsGISAXS2, IFunctionalTest>,
                 "functional test: isgisaxs ex-2 (mean form factors for particles with shape size distribution)");
    registerItem("isgisaxs03",   IFactoryCreateFunction<TestIsGISAXS3, IFunctionalTest>,
                 "functional test: isgisaxs ex-3 (cylinder FF)");
    registerItem("isgisaxs04",   IFactoryCreateFunction<TestIsGISAXS4, IFunctionalTest>,
                 "functional test: isgisaxs ex-4 (paracrystal 1d structure factors)");
    registerItem("isgisaxs05",   IFactoryCreateFunction<TestIsGISAXS5, IFunctionalTest>,
                 "functional test: isgisaxs ex-5 (fit with paracrystal 1d structure factor)");
    registerItem("isgisaxs07",   IFactoryCreateFunction<TestIsGISAXS7, IFunctionalTest>,
                 "functional test: isgisaxs ex-7 (particle mixture from morphology file)");
    registerItem("isgisaxs08",   IFactoryCreateFunction<TestIsGISAXS8, IFunctionalTest>,
                 "functional test: isgisaxs ex-8 (paracrystal lattice structure factors)");
    registerItem("isgisaxs09",   IFactoryCreateFunction<TestIsGISAXS9, IFunctionalTest>,
                 "functional test: isgisaxs ex-9 (rotated pyramid FF)");
    registerItem("isgisaxs10",  IFactoryCreateFunction<TestIsGISAXS10, IFunctionalTest>,
                 "functional test: isgisaxs ex-10 (cylinders with interference on top of substrate)");
    registerItem("isgisaxs11",  IFactoryCreateFunction<TestIsGISAXS11, IFunctionalTest>,
                 "functional test: isgisaxs ex-11 (core shell parallelopiped islands on top of substrate)");
    registerItem("isgisaxs12",  IFactoryCreateFunction<TestIsGISAXS12, IFunctionalTest>,
                 "functional test: isgisaxs ex-12 (constrained fit example)");
    registerItem("convolution", IFactoryCreateFunction<TestConvolution, IFunctionalTest>,
                 "functional test: test of convolution via fft");
    registerItem("detectorresolution", IFactoryCreateFunction<TestDetectorResolution, IFunctionalTest>,
                 "functional test: detector resolution function");
    registerItem("mesocrystal1", IFactoryCreateFunction<TestMesoCrystal1, IFunctionalTest>,
                 "functional test: mesocrystal");
    registerItem("mesocrystal2", IFactoryCreateFunction<TestMesoCrystal2, IFunctionalTest>,
                 "functional test: mesocrystal fit");
    registerItem("roottree",    IFactoryCreateFunction<TestRootTree, IFunctionalTest>,
                 "functional test: using root trees to read/write data from/to disk");
    registerItem("fitting1",     IFactoryCreateFunction<TestFittingModule1, IFunctionalTest>,
                 "functional test: fit module 2 params");
    registerItem("fitting2",     IFactoryCreateFunction<TestFittingModule2, IFunctionalTest>,
                 "functional test: fit module 5 params");
    registerItem("fitting3",     IFactoryCreateFunction<TestFittingModule3, IFunctionalTest>,
                 "functional test: fit module 4 params, 1d scans");
    registerItem("performance", IFactoryCreateFunction<TestPerformance, IFunctionalTest>,
                 "functional test: run performance test for several predefined tasks");
    registerItem("roughdwba",   IFactoryCreateFunction<TestMultiLayerRoughness, IFunctionalTest>,
                 "functional test: diffuse scattering from multi layer with roughness");
    registerItem("testmisc",    IFactoryCreateFunction<TestMiscellaneous, IFunctionalTest>,
                 "functional test: test of different miscellaneous issues");
    registerItem("fitbench",    IFactoryCreateFunction<TestFittingBenchmark, IFunctionalTest>,
                 "functional test: test of minimizers with hard-to-minimize test functions");
    registerItem("fourier",    IFactoryCreateFunction<TestFourier, IFunctionalTest>,
                 "functional test: test of Fourier transformation of OutputData maps");
    registerItem("fumili",    IFactoryCreateFunction<TestFumiliLMA, IFunctionalTest>,
                 "functional test: test of ROOT's LMA-based minimizers Fumili and GSLMultiFit");
    registerItem("toyexp",    IFactoryCreateFunction<TestToyExperiment, IFunctionalTest>,
                 "functional test: test fitting algorithms with toy experiment");

    m_benchmark = new TBenchmark();
}



FunctionalTestFactory::~FunctionalTestFactory()
{
    delete m_benchmark;
}


/* ************************************************************************* */
// print benchmark summary on the screen
/* ************************************************************************* */
void FunctionalTestFactory::print_benchmarks()
{
    std::cout << "--- TestFactory::print_benchmarks() ---" << std::endl;
    Float_t rp, cp;
    m_benchmark->Summary(rp, cp);
}


/* ************************************************************************* */
// execute specific functional tests
/* ************************************************************************* */
void FunctionalTestFactory::execute(std::string name, ProgramOptions *p_options)
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

    test->initialise(p_options);
    m_benchmark->Start(name.c_str());
    test->execute();
    m_benchmark->Stop(name.c_str());
    m_benchmark->Show(name.c_str());
    test->finalise();

}


void FunctionalTestFactory::profile(std::string name, ProgramOptions *p_options)
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

    test->initialise(p_options);
    for(int i=0; i<1; i++) test->execute();

}



/* ************************************************************************* */
// execute all registered functional tests
/* ************************************************************************* */
void FunctionalTestFactory::execute_all(ProgramOptions *p_options)
{
    CallbackMap_t::const_iterator it;
    for(it=m_callbacks.begin(); it != m_callbacks.end(); ++it ) {
        execute( it->first , p_options);
        //createItem( it->first )->execute();
    }
    print_benchmarks();
}


/* ************************************************************************* */
// print on the screen names of registered tests
/* ************************************************************************* */
void FunctionalTestFactory::print_testnames()
{
    std::string help;
    help += "TestFactory::print_testnames() -> Info. \n";
    help += "You can run few functional tests by running './App testname'\n";
    help += "List of available tests are below:";
    std::cout << help << std::endl;
    CallbackMap_t::const_iterator it;
    for(it=m_callbacks.begin(); it != m_callbacks.end(); ++it ) {
        std::cout << it->first << std::endl;
    }
}


/* ************************************************************************* */
// return vector of registered test names
/* ************************************************************************* */
FunctionalTestFactory::DescriptionMap_t FunctionalTestFactory::getDescriptionMap()
{
    return m_descriptions;
}

