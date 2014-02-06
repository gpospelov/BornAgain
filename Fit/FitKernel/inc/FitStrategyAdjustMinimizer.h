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
#include "IMinimizer.h"

//! @class FitStrategyAdjustMinimizer
//! @ingroup fitting
//! @brief Strategy modifies mimimizer settings before running minimization round

class BA_CORE_API_ FitStrategyAdjustMinimizer : public IFitStrategy
{
public:
    FitStrategyAdjustMinimizer() : m_minimizer(0) {}
    virtual ~FitStrategyAdjustMinimizer(){ delete m_minimizer; }

    virtual FitStrategyAdjustMinimizer *clone() const;

    IMinimizer *getMinimizer() { return m_minimizer; }
    void setMinimizer(IMinimizer *minimizer) { m_minimizer = minimizer; }

    virtual void execute();

private:
    IMinimizer *m_minimizer;
};

#endif // FITSTRATEGYADJUSTMINIMIZER_H

