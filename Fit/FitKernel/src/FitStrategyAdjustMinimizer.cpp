// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/FitStrategyAdjustMinimizer.cpp
//! @brief     Implements class FitStrategyAdjustMinimizer.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

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
