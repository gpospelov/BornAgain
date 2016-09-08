// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/IMinimizerTest.cpp
//! @brief     Implements class IMinimizerTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IMinimizerTest.h"
#include "FitSuite.h"
#include "GISASSimulation.h"
#include "MultiLayer.h"
#include "MinimizerFactory.h"
#include "ObsoleteMinimizerOptions.h"
#include "SampleBuilderFactory.h"
#include "SimulationFactory.h"
#include "Units.h"
#include <boost/format.hpp>
#include <memory>

IMinimizerTest::TestParameter::TestParameter(
    const std::string& name, double real_value, double start_value)
    : m_name(name), m_real_value(real_value), m_start_value(start_value), m_found_value(0.0)
{
}

IMinimizerTest::IMinimizerTest(const std::string& minimizer_name,
                               const std::string& minimizer_algorithm)
    : m_minimizer_name(minimizer_name)
    , m_minimizer_algorithm(minimizer_algorithm)
    , m_simulation_name("MiniGISAS")
    , m_sample_builder_name("CylindersInBABuilder")
    , m_parameter_tolerance(0.01)
{
    m_parameters.push_back(
        TestParameter("*Height", 5.0 * Units::nanometer, 4.5 * Units::nanometer));
    m_parameters.push_back(
        TestParameter("*Radius", 5.0 * Units::nanometer, 5.5 * Units::nanometer));
}


bool IMinimizerTest::runTest()
{
    std::unique_ptr<MultiLayer> sample(createSample());
    for (size_t i = 0; i < m_parameters.size(); ++i)
        sample->setParameterValue(m_parameters[i].m_name, m_parameters[i].m_real_value);

    std::unique_ptr<GISASSimulation> simulation(createSimulation());
    simulation->setSample(*sample.get());
    simulation->runSimulation();

    std::unique_ptr<OutputData<double> > real_data(createOutputData(simulation.get()));

    std::unique_ptr<FitSuite> fitSuite(createFitSuite());
    fitSuite->addSimulationAndRealData(*simulation.get(), *real_data.get());

    // run fit
    fitSuite->runFit();

    std::vector<double> valuesAtMinimum = fitSuite->getMinimizer()->getValueOfVariablesAtMinimum();
    for (size_t i = 0; i < m_parameters.size(); ++i)
        m_parameters[i].m_found_value = valuesAtMinimum[i];

    // analyze results
    bool success = true;
    for (size_t i = 0; i < m_parameters.size(); ++i) {
        double diff = std::abs(m_parameters[i].m_found_value - m_parameters[i].m_real_value)
                      / m_parameters[i].m_real_value;
        if (diff > m_parameter_tolerance)
            success = false;
        std::cout << boost::format("%|12t| %-10s : %-6.4f (diff %6.4g) %s\n") %
            m_parameters[i].m_name % m_parameters[i].m_found_value % diff %
            (success ? "OK" : "FAILED");
    }
    return success;
}

std::unique_ptr<FitSuite> IMinimizerTest::createFitSuite()
{
    std::unique_ptr<FitSuite> result(new FitSuite());
    result->initPrint(10);
    IMinimizer* minimizer = MinimizerFactory::createMinimizer(
        m_minimizer_name, m_minimizer_algorithm);
    minimizer->getOptions()->setMaxIterations(200);
    result->setMinimizer(minimizer);
    for (size_t i = 0; i < m_parameters.size(); ++i)
        result->addFitParameter(
            m_parameters[i].m_name, m_parameters[i].m_start_value,
            RealLimits::lowerLimited(0.01), Attributes::free(), m_parameters[i].m_start_value / 100.);
    return result;
}

std::unique_ptr<MultiLayer> IMinimizerTest::createSample()
{
    SampleBuilderFactory builderFactory;
    std::unique_ptr<MultiLayer> result(builderFactory.createSample(m_sample_builder_name));
    return result;
}

std::unique_ptr<GISASSimulation> IMinimizerTest::createSimulation()
{
    SimulationFactory simRegistry;
    std::unique_ptr<GISASSimulation> result(simRegistry.createItem(m_simulation_name));
    return result;
}

std::unique_ptr<OutputData<double> > IMinimizerTest::createOutputData(
    const GISASSimulation* simulation)
{
    std::unique_ptr<OutputData<double>> result(simulation->getDetectorIntensity());
    return result;
}
