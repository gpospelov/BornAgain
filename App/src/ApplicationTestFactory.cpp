// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/ApplicationTestFactory.cpp
//! @brief     Implements class ApplicationTestFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ApplicationTestFactory.h"
#include "TestBugs.h"
#include "TestConvolution.h"
#include "TestDetectorResolution.h"
#include "TestDiffuseReflection.h"
#include "TestFittingModule1.h"
#include "TestFittingModule2.h"
#include "TestFittingModule3.h"
#include "TestFittingModule4.h"
#include "TestFormFactor.h"
#include "TestFormFactors.h"
#include "TestFourier.h"
#include "TestFumiliLMA.h"
#include "TestIsGISAXS12.h"
#include "TestIsGISAXS13.h"
#include "TestIsGISAXS5.h"
#include "TestMesoCrystal1.h"
#include "TestMiscellaneous.h"
#include "TestMultiLayerRoughness.h"
#include "TestPerformance.h"
#include "TestPolarizedDWBA.h"
#include "TestPolarizedDWBATerms.h"
#include "TestPolarizedMeso.h"
#include "TestRootTree.h"
#include "TestRoughness.h"
#include "TestSpecularMagnetic.h"
#include "TestSpecularMatrix.h"
#include "TestToySimulation.h"
#include "TestFunctionalTests.h"
#include "TestRipple2.h"
#include "TestRipple1.h"
#include "TestBessel.h"
#include "TestPyGenerator.h"
#include "TBenchmark.h"
#include "TestRotations.h"


ApplicationTestFactory::ApplicationTestFactory() : m_benchmark(0)
{
    setOwnObjects(true);
    m_benchmark = new TBenchmark();
}


ApplicationTestFactory::~ApplicationTestFactory()
{
    delete m_benchmark;
}


// print benchmark summary on the screen
void ApplicationTestFactory::print_benchmarks()
{
    std::cout << "--- TestFactory::print_benchmarks() ---" << std::endl;
    Float_t rp, cp;
    m_benchmark->Summary(rp, cp);
}


// execute specific functional tests
void ApplicationTestFactory::execute(std::string name, ProgramOptions *p_options)
{
    IApplicationTest *test(0);
    try {
        test = createItem( name );
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        std::cout << "TestFactory::execute() -> Warning. No test with name '"
                << name << "' is defined." << std::endl;
        return;
    }

    test->initialise(p_options);
    m_benchmark->Start(name.c_str());
    test->execute();
    m_benchmark->Stop(name.c_str());
    m_benchmark->Show(name.c_str());
    test->finalise();
}


// run tests in profile mode
void ApplicationTestFactory::profile(std::string name, ProgramOptions *p_options)
{
    IApplicationTest *test(0);
    try {
        test = createItem( name );
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        std::cout << "TestFactory::execute() -> Warning. No test with name '"
                << name << "' is defined." << std::endl;
        return;
    }

    test->initialise(p_options);
    for(int i=0; i<1; i++) test->execute();

}


// execute all registered functional tests
void ApplicationTestFactory::execute_all(ProgramOptions *p_options)
{
    CallbackMap_t::const_iterator it;
    for(it=m_callbacks.begin(); it != m_callbacks.end(); ++it ) {
        execute( it->first , p_options);
        //createItem( it->first )->execute();
    }
    print_benchmarks();
}


// print on the screen names of registered tests
void ApplicationTestFactory::print_testnames()
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


void RegisterApplicationTests(ApplicationTestFactory *p_test_factory)
{
    p_test_factory->registerItem(
        "pygen",
        IFactoryCreateFunction<TestPyGenerator, IApplicationTest>,
        "Generates a python script");
    p_test_factory->registerItem(
        "roughness",
        IFactoryCreateFunction<TestRoughness, IApplicationTest>,
        "functional test: roughness parameters");
    p_test_factory->registerItem(
        "formfactor",
        IFactoryCreateFunction<TestFormFactor, IApplicationTest>,
        "functional test: some formfactor");
    p_test_factory->registerItem(
        "diffuse",
        IFactoryCreateFunction<TestDiffuseReflection, IApplicationTest>,
        "functional test: diffuse scattering from multilayer with roughness "
        "(obsolete)");
    p_test_factory->registerItem(
        "isgisaxs05",
        IFactoryCreateFunction<TestIsGISAXS5, IApplicationTest>,
        "functional test: isgisaxs ex-5 (fit with paracrystal 1d structure "
        "factor)");
    p_test_factory->registerItem(
        "isgisaxs12",
        IFactoryCreateFunction<TestIsGISAXS12, IApplicationTest>,
        "functional test: isgisaxs ex-12 (constrained fit example)");
    p_test_factory->registerItem(
        "isgisaxs13",
        IFactoryCreateFunction<TestIsGISAXS13, IApplicationTest>,
        "functional test: isgisaxs ex-13 (simulated annealing fit)");
    p_test_factory->registerItem(
        "convolution",
        IFactoryCreateFunction<TestConvolution, IApplicationTest>,
        "functional test: test of convolution via fft");
    p_test_factory->registerItem(
        "detectorresolution",
        IFactoryCreateFunction<TestDetectorResolution, IApplicationTest>,
        "functional test: detector resolution function");
    p_test_factory->registerItem(
        "mesocrystal1",
        IFactoryCreateFunction<TestMesoCrystal1, IApplicationTest>,
        "functional test: mesocrystal");
    p_test_factory->registerItem(
        "roottree",
        IFactoryCreateFunction<TestRootTree, IApplicationTest>,
        "functional test: using root trees to read/write data from/to disk");
    p_test_factory->registerItem(
        "fitting1",
        IFactoryCreateFunction<TestFittingModule1, IApplicationTest>,
        "functional test: basing fitting 2 params");
    p_test_factory->registerItem(
        "fitting2",
        IFactoryCreateFunction<TestFittingModule2, IApplicationTest>,
        "functional test: fitting with strategies");
    p_test_factory->registerItem(
        "fitting3",
        IFactoryCreateFunction<TestFittingModule3, IApplicationTest>,
        "functional test: fitting via 1D cuts");
    p_test_factory->registerItem(
        "fitting4",
        IFactoryCreateFunction<TestFittingModule4, IApplicationTest>,
        "functional test: testing genetic minimizer");
    p_test_factory->registerItem(
        "performance",
        IFactoryCreateFunction<TestPerformance, IApplicationTest>,
        "functional test: run performance test for several predefined tasks");
    p_test_factory->registerItem(
        "roughdwba",
        IFactoryCreateFunction<TestMultiLayerRoughness, IApplicationTest>,
        "functional test: diffuse scattering from multi layer with roughness");
    p_test_factory->registerItem(
        "testmisc",
        IFactoryCreateFunction<TestMiscellaneous, IApplicationTest>,
        "functional test: test of different miscellaneous issues");
    p_test_factory->registerItem(
        "Fourier",
        IFactoryCreateFunction<TestFourier, IApplicationTest>,
        "functional test: test of Fourier transformation of OutputData maps");
    p_test_factory->registerItem(
        "fumili",
        IFactoryCreateFunction<TestFumiliLMA, IApplicationTest>,
        "functional test: test of ROOT's LMA-based minimizers Fumili and "
        "GSLLMA");
    p_test_factory->registerItem(
        "toyexp",
        IFactoryCreateFunction<TestToySimulation, IApplicationTest>,
        "functional test: test fitting algorithms with toy simulation");
    p_test_factory->registerItem(
        "FormFactors",
        IFactoryCreateFunction<TestFormFactors, IApplicationTest>,
        "functional test: FormFactors");
    p_test_factory->registerItem(
        "specularmatrix",
        IFactoryCreateFunction<TestSpecularMatrix, IApplicationTest>,
        "functional test: specular reflectivity with matrix formalism");
    p_test_factory->registerItem(
        "testbugs",
        IFactoryCreateFunction<TestBugs , IApplicationTest>,
        "functional test: test bugs reported in Redmine");
    p_test_factory->registerItem(
        "specularmagnetic",
        IFactoryCreateFunction<TestSpecularMagnetic, IApplicationTest>,
        "functional test: specular reflectivity with magnetic matrix formalism");
    p_test_factory->registerItem(
        "polarizedDWBA",
        IFactoryCreateFunction<TestPolarizedDWBA, IApplicationTest>,
        "functional test: polarized DWBA (magnetic cylinders on substrate)");
    p_test_factory->registerItem(
         "polarizedDWBATerms",
         IFactoryCreateFunction<TestPolarizedDWBATerms, IApplicationTest>,
         "functional test: compare different terms in DWBA between"
         " scalar and matrix computation");
    p_test_factory->registerItem(
         "polarizedMeso",
         IFactoryCreateFunction<TestPolarizedMeso, IApplicationTest>,
         "functional test: polarized mesocrystals");
    p_test_factory->registerItem(
        "functest",
        IFactoryCreateFunction<TestFunctionalTests, IApplicationTest>,
        "Represents functional test results in graphics form");
    p_test_factory->registerItem(
        "ripple2",
        IFactoryCreateFunction<TestRipple2, IApplicationTest>,
        "test the new ripple2 formfactor");
    p_test_factory->registerItem(
        "ripple1",
        IFactoryCreateFunction<TestRipple1, IApplicationTest>,
        "test the new ripple1 formfactor");
    p_test_factory->registerItem(
        "bessel",
        IFactoryCreateFunction<TestBessel, IApplicationTest>,
        "test complex bessel functions");
    p_test_factory->registerItem(
        "rotations",
        IFactoryCreateFunction<TestRotations, IApplicationTest>,
        "Test sample rotations");

}

