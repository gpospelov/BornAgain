// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/IFitStrategy.cpp
//! @brief     Implements class IFitStrategy.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IFitStrategy.h"
#include "FitSuite.h"

void FitStrategyDefault::execute()
{
    if( !m_fit_suite ) throw NullPointerException("FitStrategyDefault::execute() -> FitSuite doesn't exists");

    // calling minimization
    m_fit_suite->minimize();
}


