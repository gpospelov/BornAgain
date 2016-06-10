// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FutestSuite.cpp
//! @brief     Implements class FutestSuite.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include <cassert>
#include <iostream>

#include "FutestRegistry.h"
#include "SimulationRegistry.h"
#include "SampleBuilderFactory.h"
#include "SubtestRegistry.h"
#include "Exceptions.h"
#include "IFormFactor.h"
#include "IntensityDataIOFactory.h"
#include "FileSystem.h"
#include "CoreFutest.h"
#include "FTDistributions.h"
#include "FutestSuite.h"

FutestSuite::FutestSuite()
    : m_formfactor(0)
    , m_ft_distribution_2d(0)
    , m_ff_registry(0)
    , m_ft2d_registry(0)
{
}

FutestSuite::~FutestSuite()
{
    delete m_formfactor;
    delete m_ff_registry;

    delete m_ft_distribution_2d;
    delete m_ft2d_registry;
}

//! Runs test (name given as command-line argument), and returns 0 for SUCCESS, or error code.

int FutestSuite::execute(int argc, char** argv) {
    // parse command-line arguments and retrieve test info from registry
    std::string test_name;
    if(argc > 1)
        test_name = std::string(argv[1]);
    m_info = FutestRegistry::instance().getItemOrExplain(test_name, getName());
    if( !m_info )
        return 1;

    // initialize subtest registry
    std::vector<std::string> subtest_names;
    if       (m_info->m_subtest_type == "None") {
        subtest_names.push_back("Default");
    } else if(m_info->m_subtest_type == "FormFactorsRegistry") {
        m_ff_registry = new TestFormFactorsRegistry;
        subtest_names = m_ff_registry->getNames();
    } else if(m_info->m_subtest_type == "FTDistributions2DRegistry") {
        m_ft2d_registry = new TestFTDistribution2DRegistry;
        subtest_names = m_ft2d_registry->getNames();
    } else
        throw RuntimeErrorException("FutestSuite -> Error. "
                                    "Unknown factory '"+m_info->m_subtest_type+"'.");
    size_t n_subtests = subtest_names.size();

    // run and analyze subtests
    int number_of_failed_tests = 0;
    for (size_t i = 0; i < n_subtests; ++i) {
        m_subtest_name = subtest_names[i];
        if(m_ff_registry) {
            delete m_formfactor;
            m_formfactor = m_ff_registry->createItem(m_subtest_name);
        }
        if(m_ft2d_registry) {
            delete m_ft_distribution_2d;
            m_ft_distribution_2d = m_ft2d_registry->createItem(m_subtest_name);
        }

        IFutest* subtest( getFutest() );
        std::cout << "FutestSuite::execute() -> " << getName()
                  << " " << i+1 << "/" << n_subtests << " (" << m_subtest_name << ")\n";
        subtest->runTest();
        subtest->analyseResults();
        if (subtest->getTestResult())
            ++number_of_failed_tests;
        std::cout << *subtest << "\n";
    }

    // report overall result
    if (n_subtests > 1)
        std::cout << "summary: " << number_of_failed_tests << " of " << n_subtests <<
            " subtests failed\n";
    return number_of_failed_tests>0;
}

IFormFactor* FutestSuite::getFormFactor() const
{
    if(!m_formfactor)
        throw NullPointerException(
            "FutestSuite::getFormFactor() -> Error. No form factor defined.");
    return m_formfactor->clone();
}

IFTDistribution2D* FutestSuite::getFTDistribution2D() const
{
    if(!m_ft_distribution_2d)
        throw NullPointerException(
            "FutestSuite::getFTDistribution2D() -> Error. "
            "No FT distribution defined.");
    return m_ft_distribution_2d->clone();
}

GISASSimulation* FutestSuite::getSimulation() const
{
    SimulationRegistry sim_registry;
    GISASSimulation* result = sim_registry.createItem(m_info->m_simulation_name);
    result->setSampleBuilder(getSampleBuilder());
    return result;
}

std::shared_ptr<class ISampleBuilder> FutestSuite::getSampleBuilder() const
{
    SampleBuilderFactory sample_factory;
    std::shared_ptr<class ISampleBuilder> sample_builder(
        sample_factory.createItem(m_info->m_sample_builder_name) );
    sample_builder->init_from(this);
    return sample_builder;
}

OutputData<double>* FutestSuite::getReferenceData() const
{
    OutputData<double>* result(nullptr);
    std::string filename = Utils::FileSystem::GetReferenceDataDir() + getReferenceFileName();

    try {
        result = IntensityDataIOFactory::readOutputData(filename);
    } catch(const std::exception& ex) {
        throw std::runtime_error(
            std::string("FutestSuite::getReferenceData() -> Exception caught: ") + ex.what() );
    }
    return result;
}

std::string FutestSuite::getReferenceFileName() const
{
    std::string result("ref_");
    result += m_info->m_test_name;
    if(m_subtest_name != "Default")
        result += std::string("_")+m_subtest_name;
    result += std::string(".int.gz");
    return result;
}

//! Constructs functional test name corresponding to the current component. The goal is to have
//! different names of test depending from the context (single test, or multi test).
std::string FutestSuite::getTestName() const
{
    std::string result = m_info->m_test_name;
    if(m_subtest_name != "Default")
        result += "_" + m_subtest_name;
    return result;
}

//! Constructs functional test description corresponding to the current component.
std::string FutestSuite::getTestDescription() const
{
    return m_info->m_test_description;
}

double FutestSuite::getTestThreshold() const
{
    return m_info->m_threshold;
}
