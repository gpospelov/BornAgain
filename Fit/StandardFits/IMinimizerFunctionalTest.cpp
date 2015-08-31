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

#include "IMinimizerFunctionalTest.h"
#include "SampleBuilderFactory.h"
#include "SimulationRegistry.h"
#include "OutputData.h"
#include "FitSuite.h"
#include "MinimizerFactory.h"
#include <boost/scoped_ptr.hpp>
#include <boost/format.hpp>


IMinimizerFunctionalTest::TestParameter::TestParameter(const std::string &name, double real_value,
                                                       double start_value, double threshold)
    : m_name(name)
    , m_real_value(real_value)
    , m_start_value(start_value)
    , m_found_value(0.0)
    , m_threshold(threshold)
{
}

IMinimizerFunctionalTest::IMinimizerFunctionalTest(const std::string &minimizer_name,
                                                   const std::string &minimizer_algorithm)
    : m_minimizer_name(minimizer_name)
    , m_minimizer_algorithm(minimizer_algorithm)
    , m_simulation_name("MiniGISAS")
    , m_sample_builder_name("CylindersInBABuilder")
{


    m_parameters.push_back(
        TestParameter("*height", 5.0 * Units::nanometer, 4.0 * Units::nanometer));
    m_parameters.push_back(
        TestParameter("*radius", 5.0 * Units::nanometer, 6.0 * Units::nanometer));
}

void IMinimizerFunctionalTest::runTest()
{
    SampleBuilderFactory builderFactory;
    boost::scoped_ptr<ISample> sample(builderFactory.createSample(m_sample_builder_name));
    for(size_t i=0; i<m_parameters.size(); ++i) {
        sample->setParameterValue(m_parameters[i].m_name, m_parameters[i].m_real_value);
    }

    SimulationRegistry simRegistry;
    boost::scoped_ptr<GISASSimulation> simulation(simRegistry.createSimulation(m_simulation_name));

    simulation->setSample(*sample.get());
    simulation->runSimulation();

    boost::scoped_ptr<OutputData<double> > real_data(simulation->getIntensityData());

    FitSuite *fitSuite = new FitSuite();
    fitSuite->initPrint(10);
    fitSuite->setMinimizer( MinimizerFactory::createMinimizer(m_minimizer_name, m_minimizer_algorithm) );
    fitSuite->addFitParameter("*height", 4.*Units::nanometer, 0.04*Units::nanometer, AttLimits::lowerLimited(0.01) );
    fitSuite->addFitParameter("*radius", 6.*Units::nanometer, 0.06*Units::nanometer, AttLimits::lowerLimited(0.01) );
    fitSuite->addSimulationAndRealData(*simulation.get(), *real_data.get());

    // run fit
    fitSuite->runFit();

    for(size_t i=0; i<m_parameters.size(); ++i) {
        m_parameters[i].m_found_value = fitSuite->getMinimizer()->getValueOfVariableAtMinimum(i);
    }


}

int IMinimizerFunctionalTest::analyseResults()
{
    for(size_t i=0; i<m_parameters.size(); ++i) {
        double diff = std::abs(m_parameters[i].m_found_value - m_parameters[i].m_real_value)/m_parameters[i].m_real_value;
        if(diff > m_parameters[i].m_threshold) m_result = FAILED;
        std::cout << boost::format("%|12t| %-10s : %-6.4f (diff %6.4g) \n") % m_parameters[i].m_name % m_parameters[i].m_found_value % diff;
    }

    printResults(std::cout);

    return m_result;
}



