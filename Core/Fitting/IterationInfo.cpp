// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/IterationInfo.cpp
//! @brief     Implements class IterationInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IterationInfo.h"


IterationInfo::IterationInfo()
    : m_chi2(0.0)
{

}

IterationInfo::IterationInfo(const Fit::Parameters& params, double chi2)
    : m_chi2(chi2)
    , m_current_parameters(params)
{

}

double IterationInfo::chi2() const
{
    return m_chi2;
}

Fit::Parameters IterationInfo::parameters() const
{
    return m_current_parameters;
}
