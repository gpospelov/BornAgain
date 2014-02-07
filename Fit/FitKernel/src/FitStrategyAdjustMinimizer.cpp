#include "FitStrategyAdjustMinimizer.h"
#include "FitSuite.h"
#include "MinimizerFactory.h"


// It's not real clone
FitStrategyAdjustMinimizer *FitStrategyAdjustMinimizer::clone() const
{
    FitStrategyAdjustMinimizer *result = new FitStrategyAdjustMinimizer();
    result->setMinimizer( MinimizerFactory::createMinimizer(m_minimizer));
    return result;
}


void FitStrategyAdjustMinimizer::execute()
{

    m_fit_suite->setMinimizer( MinimizerFactory::createMinimizer(m_minimizer) );

    m_fit_suite->minimize();

    //m_fit_suite->printResults();

}
