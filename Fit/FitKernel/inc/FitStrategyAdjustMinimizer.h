// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/FitStrategyAdjustMinimizer.h
//! @brief     Defines class FitStrategyAdjustMinimizer
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSTRATEGYADJUSTMINIMIZER_H
#define FITSTRATEGYADJUSTMINIMIZER_H

#include "IFitStrategy.h"
#include "IMinimizer.h"

class MinimizerOptions;

//! @class FitStrategyAdjustMinimizer
//! @ingroup fitting
//! @brief Strategy modifies mimimizer settings before running minimization round

class BA_CORE_API_ FitStrategyAdjustMinimizer : public IFitStrategy
{
public:    
    FitStrategyAdjustMinimizer();

    FitStrategyAdjustMinimizer(const std::string& minimizer_name,
                               const std::string& algorithm_name = std::string(),
                               const std::string& minimizer_options=std::string());

    virtual ~FitStrategyAdjustMinimizer();

    virtual FitStrategyAdjustMinimizer *clone() const;

    IMinimizer *getMinimizer();
    void setMinimizer(IMinimizer *minimizer);

    void setMinimizer(const std::string& minimizer_name,
                      const std::string& algorithm_name = std::string(),
                      const std::string& minimizer_options=std::string());

    virtual void execute();

    virtual MinimizerOptions *getMinimizerOptions();

protected:
    virtual void print(std::ostream &ostr) const;

private:
    IMinimizer *m_minimizer;
};

#endif // FITSTRATEGYADJUSTMINIMIZER_H

