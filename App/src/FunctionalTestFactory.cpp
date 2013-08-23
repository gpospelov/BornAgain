// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/FunctionalTestFactory.cpp
//! @brief     Implements class FunctionalTestFactory.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FunctionalTestFactory.h"
#include "TestBugs.h"
#include "TestConvolution.h"
#include "TestDetectorResolution.h"
#include "TestDiffuseReflection.h"
#include "TestFittingBenchmark.h"
#include "TestFittingModule1.h"
#include "TestFittingModule2.h"
#include "TestFittingModule3.h"
#include "TestFormFactor.h"
#include "TestFormFactors.h"
#include "TestFourier.h"
#include "TestFresnelCoeff.h"
#include "TestFumiliLMA.h"
#include "TestIsGISAXS10.h"
#include "TestIsGISAXS11.h"
#include "TestIsGISAXS12.h"
#include "TestIsGISAXS13.h"
#include "TestIsGISAXS14.h"
#include "TestIsGISAXS15.h"
#include "TestIsGISAXS1.h"
#include "TestIsGISAXS2.h"
#include "TestIsGISAXS3.h"
#include "TestIsGISAXS4.h"
#include "TestIsGISAXS5.h"
#include "TestIsGISAXS6.h"
#include "TestIsGISAXS7.h"
#include "TestIsGISAXS8.h"
#include "TestIsGISAXS9.h"
#include "TestMesoCrystal1.h"
#include "TestMesoCrystal2.h"
#include "TestMiscellaneous.h"
#include "TestMultiLayerRoughness.h"
#include "TestPerformance.h"
#include "TestPolarizedDWBA.h"
#include "TestRootTree.h"
#include "TestRoughness.h"
#include "TestSpecularMagnetic.h"
#include "TestSpecularMatrix.h"
#include "TestToySimulation.h"

#include "TBenchmark.h"


FunctionalTestFactory::FunctionalTestFactory() : m_benchmark(0)
{
    setOwnObjects(true);
    m_benchmark = new TBenchmark();
}


FunctionalTestFactory::~FunctionalTestFactory()
{
    delete m_benchmark;
}


// print benchmark summary on the screen
void FunctionalTestFactory::print_benchmarks()
{
    std::cout << "--- TestFactory::print_benchmarks() ---" << std::endl;
    Float_t rp, cp;
    m_benchmark->Summary(rp, cp);
}


// execute specific functional tests
void FunctionalTestFactory::execute(std::string name, ProgramOptions *p_options)
{
    IFunctionalTest *test(0);
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
void FunctionalTestFactory::profile(std::string name, ProgramOptions *p_options)
{
    IFunctionalTest *test(0);
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
void FunctionalTestFactory::execute_all(ProgramOptions *p_options)
{
    CallbackMap_t::const_iterator it;
    for(it=m_callbacks.begin(); it != m_callbacks.end(); ++it ) {
        execute( it->first , p_options);
        //createItem( it->first )->execute();
    }
    print_benchmarks();
}


// print on the screen names of registered tests
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


void RegisterFunctionalTests(FunctionalTestFactory *p_test_factory)
{
    p_test_factory->registerItem(
        "roughness",
        IFactoryCreateFunction<TestRoughness, IFunctionalTest>,
        "functional test: roughness parameters");
    p_test_factory->registerItem(
        "Fresnel",
        IFactoryCreateFunction<TestFresnelCoeff, IFunctionalTest>,
        "functional test: Fresnel coefficients calculations");
    p_test_factory->registerItem(
        "formfactor",
        IFactoryCreateFunction<TestFormFactor, IFunctionalTest>,
        "functional test: some formfactor");
    p_test_factory->registerItem(
        "diffuse",
        IFactoryCreateFunction<TestDiffuseReflection, IFunctionalTest>,
        "functional test: diffuse scattering from multilayer with roughness "
        "(obsolete)");
    p_test_factory->registerItem(
        "isgisaxs01",
        IFactoryCreateFunction<TestIsGISAXS1, IFunctionalTest>,
        "functional test: isgisaxs ex-1 (2 types of particles without "
        "interference on top of substrate)");
    p_test_factory->registerItem(
        "isgisaxs02",
        IFactoryCreateFunction<TestIsGISAXS2, IFunctionalTest>,
        "functional test: isgisaxs ex-2 (mean form factors for particles with "
        "shape size distribution)");
    p_test_factory->registerItem(
        "isgisaxs03",
        IFactoryCreateFunction<TestIsGISAXS3, IFunctionalTest>,
        "functional test: isgisaxs ex-3 (cylinder FF)");
    p_test_factory->registerItem(
        "isgisaxs04",
        IFactoryCreateFunction<TestIsGISAXS4, IFunctionalTest>,
        "functional test: isgisaxs ex-4 (paracrystal 1d structure factors)");
    p_test_factory->registerItem(
        "isgisaxs05",
        IFactoryCreateFunction<TestIsGISAXS5, IFunctionalTest>,
        "functional test: isgisaxs ex-5 (fit with paracrystal 1d structure "
        "factor)");
    p_test_factory->registerItem(
        "isgisaxs06",
        IFactoryCreateFunction<TestIsGISAXS6, IFunctionalTest>,
        "functional test: isgisaxs ex-6 (cylinders with lattice interference "
        "function)");
    p_test_factory->registerItem(
        "isgisaxs07",
        IFactoryCreateFunction<TestIsGISAXS7, IFunctionalTest>,
        "functional test: isgisaxs ex-7 (particle mixture from morphology "
        "file)");
    p_test_factory->registerItem(
        "isgisaxs08",
        IFactoryCreateFunction<TestIsGISAXS8, IFunctionalTest>,
        "functional test: isgisaxs ex-8 (paracrystal lattice structure "
        "factors)");
    p_test_factory->registerItem(
        "isgisaxs09",
        IFactoryCreateFunction<TestIsGISAXS9, IFunctionalTest>,
        "functional test: isgisaxs ex-9 (rotated pyramid FF)");
    p_test_factory->registerItem(
        "isgisaxs10",
        IFactoryCreateFunction<TestIsGISAXS10, IFunctionalTest>,
        "functional test: isgisaxs ex-10 (cylinders with interference on top "
        "of substrate)");
    p_test_factory->registerItem(
        "isgisaxs11",
        IFactoryCreateFunction<TestIsGISAXS11, IFunctionalTest>,
        "functional test: isgisaxs ex-11 (core shell parallelopiped islands "
        "on top of substrate)");
    p_test_factory->registerItem(
        "isgisaxs12",
        IFactoryCreateFunction<TestIsGISAXS12, IFunctionalTest>,
        "functional test: isgisaxs ex-12 (constrained fit example)");
    p_test_factory->registerItem(
        "isgisaxs13",
        IFactoryCreateFunction<TestIsGISAXS13, IFunctionalTest>,
        "functional test: isgisaxs ex-13 (simulated annealing fit)");
    p_test_factory->registerItem(
        "isgisaxs14",
        IFactoryCreateFunction<TestIsGISAXS14, IFunctionalTest>,
        "functional test: isgisaxs ex-14 (multilayered sphere on graded "
        "interface)");
    p_test_factory->registerItem(
        "isgisaxs15",
        IFactoryCreateFunction<TestIsGISAXS15, IFunctionalTest>,
        "functional test: isgisaxs ex-15 (size-spacing correlation "
        "approximation)");
    p_test_factory->registerItem(
        "convolution",
        IFactoryCreateFunction<TestConvolution, IFunctionalTest>,
        "functional test: test of convolution via fft");
    p_test_factory->registerItem(
        "detectorresolution",
        IFactoryCreateFunction<TestDetectorResolution, IFunctionalTest>,
        "functional test: detector resolution function");
    p_test_factory->registerItem(
        "mesocrystal1",
        IFactoryCreateFunction<TestMesoCrystal1, IFunctionalTest>,
        "functional test: mesocrystal");
    p_test_factory->registerItem(
        "mesocrystal2",
        IFactoryCreateFunction<TestMesoCrystal2, IFunctionalTest>,
        "functional test: mesocrystal fit");
    p_test_factory->registerItem(
        "roottree",
        IFactoryCreateFunction<TestRootTree, IFunctionalTest>,
        "functional test: using root trees to read/write data from/to disk");
    p_test_factory->registerItem(
        "fitting1",
        IFactoryCreateFunction<TestFittingModule1, IFunctionalTest>,
        "functional test: fit module 2 params");
    p_test_factory->registerItem(
        "fitting2",
        IFactoryCreateFunction<TestFittingModule2, IFunctionalTest>,
        "functional test: fit module 5 params");
    p_test_factory->registerItem(
        "fitting3",
        IFactoryCreateFunction<TestFittingModule3, IFunctionalTest>,
        "functional test: fit module 4 params, 1d scans");
    p_test_factory->registerItem(
        "performance",
        IFactoryCreateFunction<TestPerformance, IFunctionalTest>,
        "functional test: run performance test for several predefined tasks");
    p_test_factory->registerItem(
        "roughdwba",
        IFactoryCreateFunction<TestMultiLayerRoughness, IFunctionalTest>,
        "functional test: diffuse scattering from multi layer with roughness");
    p_test_factory->registerItem(
        "testmisc",
        IFactoryCreateFunction<TestMiscellaneous, IFunctionalTest>,
        "functional test: test of different miscellaneous issues");
    p_test_factory->registerItem(
        "fitbench",
        IFactoryCreateFunction<TestFittingBenchmark, IFunctionalTest>,
        "functional test: test of minimizers with hard-to-minimize test "
        "functions");
    p_test_factory->registerItem(
        "Fourier",
        IFactoryCreateFunction<TestFourier, IFunctionalTest>,
        "functional test: test of Fourier transformation of OutputData maps");
    p_test_factory->registerItem(
        "fumili",
        IFactoryCreateFunction<TestFumiliLMA, IFunctionalTest>,
        "functional test: test of ROOT's LMA-based minimizers Fumili and "
        "GSLMultiFit");
    p_test_factory->registerItem(
        "toyexp",
        IFactoryCreateFunction<TestToySimulation, IFunctionalTest>,
        "functional test: test fitting algorithms with toy simulation");
    p_test_factory->registerItem(
        "FormFactors",
        IFactoryCreateFunction<TestFormFactors, IFunctionalTest>,
        "functional test: FormFactors");
    p_test_factory->registerItem(
        "specularmatrix",
        IFactoryCreateFunction<TestSpecularMatrix, IFunctionalTest>,
        "functional test: specular reflectivity with matrix formalism");
    p_test_factory->registerItem(
        "testbugs",
        IFactoryCreateFunction<TestBugs , IFunctionalTest>,
        "functional test: test bugs reported in Redmine");
    p_test_factory->registerItem(
        "specularmagnetic",
        IFactoryCreateFunction<TestSpecularMagnetic, IFunctionalTest>,
        "functional test: specular reflectivity with magnetic matrix formalism");
    p_test_factory->registerItem(
        "polarizedDWBA",
        IFactoryCreateFunction<TestPolarizedDWBA, IFunctionalTest>,
        "functional test: polarized DWBA (magnetic cylinders on substrate)");
}

