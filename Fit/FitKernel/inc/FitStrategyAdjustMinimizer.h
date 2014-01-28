// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/FitStrategyAdjustMinimizer.h
//! @brief     Defines class FitStrategyAdjustMinimizer
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSTRATEGYADJUSTMINIMIZER_H
#define FITSTRATEGYADJUSTMINIMIZER_H

#include "IFitStrategy.h"

//! @class FitStrategyAdjustMinimizer
//! @ingroup fitting
//! @brief Strategy modifies mimimizer settings before running minimization round

class BA_CORE_API_ FitStrategyAdjustMinimizer : public IFitStrategy
{
public:
};

#endif // FITSTRATEGYADJUSTMINIMIZER_H

