#include "IFitStrategy.h"
#include "FitSuite.h"

void FitStrategyDefault::execute()
{
    if( !m_fit_suite ) throw NullPointerException("FitStrategyDefault::execute() -> FitSuite doesn't exists");

    // calling minimization
    m_fit_suite->minimize();
}


