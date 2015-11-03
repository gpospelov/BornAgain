#include "MinimizerFunctionalTests.h"
#include "FitSuite.h"
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

FitSuite *GSLSimulatedAnnealingTest::createFitSuite()
{
    setParameterTolerance(0.1);
    FitSuite *result = new FitSuite();
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

    return result;
}


GeneticTest::GeneticTest()
    : IMinimizerFunctionalTest("Genetic")
{}

FitSuite *GeneticTest::createFitSuite()
{
    setParameterTolerance(0.1);
    FitSuite *result = new FitSuite();
    result->initPrint(200);
    IMinimizer *minimizer = MinimizerFactory::createMinimizer(m_minimizer_name, m_minimizer_algorithm);
    minimizer->getOptions()->setMaxIterations(1);
    minimizer->getOptions()->setValue("RandomSeed",1);
    result->setMinimizer(minimizer);
    for (size_t i = 0; i < m_parameters.size(); ++i) {
        result->addFitParameter(m_parameters[i].m_name, m_parameters[i].m_start_value,
                                    AttLimits::limited(4.0, 6.0), m_parameters[i].m_start_value / 100.);
    }

    return result;
}
