// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/IterationInfo.h
//! @brief     Defines class IterationInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ITERATIONINFO_H
#define ITERATIONINFO_H

#include "WinDllMacros.h"
#include "Parameters.h"

//! Stores fit iteration info to track fit flow from various observers.
//! Used in context of FitObjective.

class BA_CORE_API_ IterationInfo
{
public:
    IterationInfo();
    IterationInfo(const Fit::Parameters& params, double chi2);

    double chi2() const;

    Fit::Parameters parameters() const;

private:
    double m_chi2;
    Fit::Parameters m_current_parameters;
};


#endif // ITERATIONINFO_H
