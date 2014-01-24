// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/FitStrategyAdjustParameters.h
//! @brief     Defines classes FitStrategyAdjustParameters and related
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSTRATEGYADJUSTPARAMETERS_H
#define FITSTRATEGYADJUSTPARAMETERS_H

#include "IFitStrategy.h"

//! @class FitStrategyAdjustParameters
//! @ingroup fitting_internal
//! @brief Strategy which fixes/releases fit parameters and call minimizer

class BA_CORE_API_ FitStrategyAdjustParameters : public IFitStrategy
{
public:
    FitStrategyAdjustParameters(const std::string& name)
        : IFitStrategy(name)
        , m_fix_all(false)
        , m_release_all(false)
        , m_preserve_original_values(false) { }
    FitStrategyAdjustParameters()
        : IFitStrategy("FitSuiteStrategyAdjustParameters")
        , m_fix_all(false)
        , m_release_all(false)
        , m_preserve_original_values(false)  { }    
    virtual ~FitStrategyAdjustParameters(){}

    virtual FitStrategyAdjustParameters *clone() const { return new FitStrategyAdjustParameters(*this); }

    virtual void execute();
    FitStrategyAdjustParameters& fix_all() {
        m_fix_all = true; return *this;
    }
    FitStrategyAdjustParameters& release_all() {
        m_release_all = true; return *this;
    }
    FitStrategyAdjustParameters& fix(std::string parname ) {
        m_pars_to_fix.push_back(parname);
        return *this;
    }
    FitStrategyAdjustParameters& release(std::string parname ) {
        m_pars_to_release.push_back(parname);
        return *this;
    }
    void setPreserveOriginalValues(bool preserve_values) {
        m_preserve_original_values = preserve_values;
    }

protected:
    FitStrategyAdjustParameters(const FitStrategyAdjustParameters &other);

    bool m_fix_all;
    bool m_release_all;
    std::vector<std::string > m_pars_to_fix;
    std::vector<std::string > m_pars_to_release;
    //! if it's true, strategy will set back values of parameters as they were
    //! before minimization round
    bool m_preserve_original_values;
};


#endif  // FITSTRATEGYADJUSTPARAMETERS_H
