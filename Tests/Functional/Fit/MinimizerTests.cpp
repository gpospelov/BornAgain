// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/MinimizerTests.cpp
//! @brief     Implements classes MinimizerTests.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MinimizerTests.h"
#include "MinimizerOptions.h"
#include "FitSuite.h"
#include "MinimizerFactory.h"

Minuit2MigradTest::Minuit2MigradTest()
    : IMinimizerTest("Minuit2", "Migrad")
{}

Minuit2FumiliTest::Minuit2FumiliTest()
    : IMinimizerTest("Minuit2", "Fumili")
{}

GSLLevenbergMarquardtTest::GSLLevenbergMarquardtTest()
    : IMinimizerTest("GSLLMA")
{}


GSLMultiMinBFGSTest::GSLMultiMinBFGSTest()
    : IMinimizerTest("GSLMultiMin", "BFGS")
{}


GSLMultiMinSteepestDescentTest::GSLMultiMinSteepestDescentTest()
    : IMinimizerTest("GSLMultiMin", "SteepestDescent")
{}


GSLSimulatedAnnealingTest::GSLSimulatedAnnealingTest()
    : IMinimizerTest("GSLSimAn")
{}

std::unique_ptr<FitSuite> GSLSimulatedAnnealingTest::createFitSuite()
{
    setParameterTolerance(0.1);
    std::unique_ptr<FitSuite> result(new FitSuite());
    result->initPrint(200);
    IMinimizer* minimizer =
        MinimizerFactory::createMinimizer(m_minimizer_name, m_minimizer_algorithm);
//    minimizer->getOptions().setValue("ntries", 10);
    minimizer->getOptions()->setValue("niters_fixed_t", 5);
    minimizer->getOptions()->setMaxIterations(10);
    minimizer->getOptions()->setValue("t_min", 1.0);
    result->setMinimizer(minimizer);
    for (const auto& par: m_parameters)
        result->addFitParameter(
            par.m_name, par.m_start_value,
            RealLimits::limited(4.0, 6.0), Attributes::free(), par.m_start_value/100.);
    return result;
}


GeneticTest::GeneticTest()
    : IMinimizerTest("Genetic")
{}

std::unique_ptr<FitSuite> GeneticTest::createFitSuite()
{
    setParameterTolerance(0.1);
    std::unique_ptr<FitSuite> result(new FitSuite());
    result->initPrint(200);
    IMinimizer* minimizer =
        MinimizerFactory::createMinimizer(m_minimizer_name, m_minimizer_algorithm);
    minimizer->getOptions()->setMaxIterations(1);
    minimizer->getOptions()->setValue("RandomSeed",1);
    result->setMinimizer(minimizer);
    for (const auto& par: m_parameters)
        result->addFitParameter(
            par.m_name, par.m_start_value,
            RealLimits::limited(4.0, 6.0), Attributes::free(), par.m_start_value/100.);
    return result;
}
