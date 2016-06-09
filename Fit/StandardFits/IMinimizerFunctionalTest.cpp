// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardFits/IMinimizerFunctionalTest.cpp
//! @brief     Implements class IMinimizerFunctionalTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Units.h"
#include "FitKernel.h"
#include "SampleBuilderFactory.h"
#include "SimulationRegistry.h"
#include "OutputData.h"
#include "FitSuite.h"
#include "IMinimizerFunctionalTest.h"
#include "MinimizerFactory.h"
#include <memory>
#include <boost/format.hpp>

IMinimizerFunctionalTest::TestParameter::TestParameter(const std::string &name, double real_value,
                                                       double start_value)
    : m_name(name), m_real_value(real_value), m_start_value(start_value), m_found_value(0.0)
{
}

IMinimizerFunctionalTest::IMinimizerFunctionalTest(const std::string &minimizer_name,
                                                   const std::string &minimizer_algorithm)
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


void IMinimizerFunctionalTest::runTest()
{
    std::unique_ptr<ISample> sample(createSample());
    for (size_t i = 0; i < m_parameters.size(); ++i) {
        sample->setParameterValue(m_parameters[i].m_name, m_parameters[i].m_real_value);
    }

    std::unique_ptr<GISASSimulation> simulation(createSimulation());
    simulation->setSample(*sample.get());
    simulation->runSimulation();

    std::unique_ptr<OutputData<double> > real_data(createOutputData(simulation.get()));

    std::unique_ptr<FitSuite> fitSuite(createFitSuite());
    fitSuite->addSimulationAndRealData(*simulation.get(), *real_data.get());

    // run fit
    fitSuite->runFit();

    for (size_t i = 0; i < m_parameters.size(); ++i) {
        m_parameters[i].m_found_value = fitSuite->getMinimizer()->getValueOfVariableAtMinimum(i);
    }
}

int IMinimizerFunctionalTest::analyseResults()
{
    for (size_t i = 0; i < m_parameters.size(); ++i) {
        double diff = std::abs(m_parameters[i].m_found_value - m_parameters[i].m_real_value)
                      / m_parameters[i].m_real_value;
        if (diff > m_parameter_tolerance)
            m_result = FAILED;
        std::cout << boost::format("%|12t| %-10s : %-6.4f (diff %6.4g) \n") % m_parameters[i].m_name
                     % m_parameters[i].m_found_value % diff;
    }

    std::cout << getName() << " | " << getDescription() << " | " << getTestResultString() << std::endl;

    return m_result;
}

void IMinimizerFunctionalTest::setParameterTolerance(double value)
{
    m_parameter_tolerance = value;
}


std::unique_ptr<FitSuite> IMinimizerFunctionalTest::createFitSuite()
{
    std::unique_ptr<FitSuite> result(new FitSuite());
    result->initPrint(10);
    IMinimizer *minimizer = MinimizerFactory::createMinimizer(
        m_minimizer_name, m_minimizer_algorithm);
    minimizer->getOptions()->setMaxIterations(200);
    result->setMinimizer(minimizer);
    for (size_t i = 0; i < m_parameters.size(); ++i) {
        result->addFitParameter(m_parameters[i].m_name, m_parameters[i].m_start_value,
                                AttLimits::lowerLimited(0.01), m_parameters[i].m_start_value / 100.);
    }

    return std::move(result);
}

std::unique_ptr<ISample> IMinimizerFunctionalTest::createSample()
{
    SampleBuilderFactory builderFactory;
    std::unique_ptr<ISample> result(builderFactory.createSample(m_sample_builder_name));
    return std::move(result);
}

std::unique_ptr<GISASSimulation> IMinimizerFunctionalTest::createSimulation()
{
    SimulationRegistry simRegistry;
    std::unique_ptr<GISASSimulation> result(simRegistry.createItem(m_simulation_name));
    return std::move(result);
}

std::unique_ptr<OutputData<double> > IMinimizerFunctionalTest::createOutputData(
    const GISASSimulation *simulation)
{
    std::unique_ptr<OutputData<double> > result(simulation->getDetectorIntensity());
    return std::move(result);
}
