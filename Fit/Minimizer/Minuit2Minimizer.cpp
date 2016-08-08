// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/Minuit2Minimizer.h
//! @brief     Declares class Minuit2Minimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Minuit2Minimizer.h"
#include "AlgorithmNames.h"

Minuit2Minimizer::Minuit2Minimizer()
    : BasicMinimizer(MinimizerNames::Minuit, AlgorithmNames::Migrad)
{
    addOption(std::string("Strategy"), 1);
    addOption(std::string("ErrorDef"), 1);

    MinimizerOption::variant_t v;
    v.get<int>();



}
