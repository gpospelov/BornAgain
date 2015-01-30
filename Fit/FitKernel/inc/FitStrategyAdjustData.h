// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/FitStrategyAdjustData.h
//! @brief     Defines class FitStrategyAdjustData
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSTRATEGYADJUSTDATA_H
#define FITSTRATEGYADJUSTDATA_H

#include "IFitStrategy.h"

//! @class FitStrategyAdjustData
//! @ingroup fitting
//! @brief Strategy modifies data before running minimization round

class BA_CORE_API_ FitStrategyAdjustData : public IFitStrategy
{
public:
    FitStrategyAdjustData(int power_of_two = 1,
            bool preserve_original=true, bool call_minimize=true)
        : IFitStrategy("FitStrategyAdjustData")
        , m_power_of_two(power_of_two)
        , m_preserve_original_data(preserve_original)
        , m_call_minimize(call_minimize) { }

    virtual FitStrategyAdjustData *clone() const { return new FitStrategyAdjustData(*this); }

    void setPreserveOriginalData(bool preserve_original) {
        m_preserve_original_data = preserve_original;
    }
    void setCallMinimize(bool call_minimize) {
        m_call_minimize = call_minimize;
    }
    virtual void execute();
protected:
    FitStrategyAdjustData(const FitStrategyAdjustData &other);

    size_t m_power_of_two;
    //! if it is true, strategy will restore original data in FitSuite
    //! before exiting
    bool m_preserve_original_data;
    //! if it's true, modify data and then call FitSuite's minimizer,
    //! if false - simply modify the data
    bool m_call_minimize;
};

#endif // FITSTRATEGYADJUSTDATA_H

