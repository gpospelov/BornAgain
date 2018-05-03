// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/NewKernel/MinimizerResult.h
//! @brief     Defines class MinimizerResult.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MINIMIZERRESULT_H
#define MINIMIZERRESULT_H

#include "WinDllMacros.h"
#include "Parameters.h"
#include <string>

namespace Fit {

//! Result of minimization round.

class BA_CORE_API_ MinimizerResult
{
public:
    MinimizerResult();

    void setParameters(const Parameters& parameters);
    Parameters parameters() const;

    void setMinValue(double value);
    double minValue() const;

    std::string toString() const;

    void setReport(const std::string& value);

private:
    Parameters m_parameters;
    double m_min_value;
    std::string m_minimizer_report;
};

}  // namespace Fit

#endif
