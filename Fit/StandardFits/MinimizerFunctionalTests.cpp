// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardFits/MinimizerFunctionalTests.cpp
//! @brief     Implements classes MinimizerFunctionalTests.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MinimizerFunctionalTests.h"
#include "FitSuite.h"
#include "FitKernel.h"
#include "MinimizerFactory.h"

Minuit2MigradTest::Minuit2MigradTest()
    : IMinimizerFunctionalTest("Minuit2", "Migrad")
{}

Minuit2FumiliTest::Minuit2FumiliTest()
    : IMinimizerFunctionalTest("Minuit2", "Fumili")
{}

GSLLevenbergMarquardtTest::GSLLevenbergMarquardtTest()
    : IMinimizerFunctionalTest("GSLLMA")
{}


GSLMultiMinBFGSTest::GSLMultiMinBFGSTest()
    : IMinimizerFunctionalTest("GSLMultiMin", "BFGS")
{}


GSLMultiMinSteepestDescentTest::GSLMultiMinSteepestDescentTest()
    : IMinimizerFunctionalTest("GSLMultiMin", "SteepestDescent")
{}


GSLSimulatedAnnealingTest::GSLSimulatedAnnealingTest()
    : IMinimizerFunctionalTest("GSLSimAn")
{}

std::unique_ptr<FitSuite> GSLSimulatedAnnealingTest::createFitSuite()
{
    setParameterTolerance(0.1);
    std::unique_ptr<FitSuite> result(new FitSuite());
    result->initPrint(200);
    IMinimizer *minimizer = MinimizerFactory::createMinimizer(m_minimizer_name, m_minimizer_algorithm);
//    minimizer->getOptions().setValue("ntries", 10);
    minimizer->getOptions()->setValue("niters_fixed_t", 5);
    minimizer->getOptions()->setMaxIterations(10);
    minimizer->getOptions()->setValue("t_min", 1.0);
    result->setMinimizer(minimizer);
    for (size_t i = 0; i < m_parameters.size(); ++i) {
        result->addFitParameter(m_parameters[i].m_name, m_parameters[i].m_start_value,
                                    AttLimits::limited(4.0, 6.0), m_parameters[i].m_start_value / 100.);
    }

    return std::move(result);
}


GeneticTest::GeneticTest()
    : IMinimizerFunctionalTest("Genetic")
{}

std::unique_ptr<FitSuite> GeneticTest::createFitSuite()
{
    setParameterTolerance(0.1);
    std::unique_ptr<FitSuite> result(new FitSuite());
    result->initPrint(200);
    IMinimizer *minimizer = MinimizerFactory::createMinimizer(m_minimizer_name, m_minimizer_algorithm);
    minimizer->getOptions()->setMaxIterations(1);
    minimizer->getOptions()->setValue("RandomSeed",1);
    result->setMinimizer(minimizer);
    for (size_t i = 0; i < m_parameters.size(); ++i) {
        result->addFitParameter(m_parameters[i].m_name, m_parameters[i].m_start_value,
                                    AttLimits::limited(4.0, 6.0), m_parameters[i].m_start_value / 100.);
    }

    return std::move(result);
}
