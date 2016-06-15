// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/TestMachinery/FutestSuite.cpp
//! @brief     Implements class FutestSuite.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include <iostream>

#include "FutestRegistry.h"
#include "SimulationFactory.h"
#include "SampleBuilderFactory.h"
#include "SubtestRegistry.h"
#include "IFutest.h"
#include "Exceptions.h"
#include "FutestSuite.h"

// ************************************************************************** //
//  Test execution
// ************************************************************************** //

//! Runs test (name given as command-line argument), and returns 0 for SUCCESS, or error code.

int FutestSuite::execute(int argc, char** argv) {
    // parse command-line arguments and retrieve test info from registry
    std::string test_name;
    if(argc > 1)
        test_name = std::string(argv[1]);
    m_info = FutestRegistry::instance().getItemOrExplain(test_name, getName());
    if( !m_info )
        return 1;

    if (m_info->m_subtest_type == "None")
        return execute_onetest();
    else
        return execute_subtests();
}

//! Runs a single test, and returns 0 for SUCCESS, or error code.

int FutestSuite::execute_onetest()
{
    m_test_name = m_info->m_test_name;
    IFutest* test( getFutest() );
    test->runTest();
    test->analyseResults();
    std::cout << *test << "\n";
    return test->getTestResult();
}

//! Runs all available subtests, and returns 0 if all succeed, or 1 in case of any error.

int FutestSuite::execute_subtests()
{
    // initialize subtest registry
    std::vector<std::string> subtest_names;
    IRegistry<IParameterized>* subtest_registry;
    if       (m_info->m_subtest_type == "FormFactorsRegistry") {
        subtest_registry = new TestFormFactorsRegistry;
    } else if(m_info->m_subtest_type == "FTDistributions2DRegistry") {
        subtest_registry = new TestFTDistribution2DRegistry;
    } else
        throw RuntimeErrorException("FutestSuite -> Error. "
                                    "Unknown factory '"+m_info->m_subtest_type+"'.");
    subtest_names = subtest_registry->keys();
    size_t n_subtests = subtest_names.size();

    // run and analyze subtests
    int number_of_failed_tests = 0;
    for (size_t i = 0; i < n_subtests; ++i) {
        m_test_name = m_info->m_test_name + "_" + subtest_names[i];
        m_subtest_item = subtest_registry->getItem(subtest_names[i]);

        IFutest* subtest( getFutest() );
        std::cout << "FutestSuite::execute() -> " << getName()
                  << " " << i+1 << "/" << n_subtests << " (" << subtest_names[i] << ")\n";
        subtest->runTest();
        subtest->analyseResults();
        std::cout << *subtest << "\n";
        if (subtest->getTestResult())
            ++number_of_failed_tests;
    }
    delete subtest_registry;

    // report overall result
    std::cout << "summary: " << number_of_failed_tests << " of " << n_subtests <<
        " subtests failed\n";
    return number_of_failed_tests>0;
}

// ************************************************************************** //
//  Functions called by getFutest() in *Suite.cpp
// ************************************************************************** //

GISASSimulation* FutestSuite::getSimulation() const
{
    SimulationFactory sim_registry;
    GISASSimulation* result = sim_registry.createItem(m_info->m_simulation_name);
    SampleBuilderFactory sample_factory;
    std::shared_ptr<class ISampleBuilder> sample_builder(
        sample_factory.createItem(m_info->m_sample_builder_name) );
    if(m_subtest_item)
        sample_builder->set_subtest(m_subtest_item);
    result->setSampleBuilder(sample_builder);
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
