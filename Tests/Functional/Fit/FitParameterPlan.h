// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitParameterPlan.h
//! @brief     Declares class FitParameterPlan.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITPARAMETERPLAN_H
#define FITPARAMETERPLAN_H

#include "AttLimits.h"

//! @class FitParameterPlan
//! @ingroup standard_samples
//! @brief The FitParameterPlan defines fit parameter settings and the value which has to be found
//! in the course of minimization.

class FitParameterPlan
{
public:
    FitParameterPlan(double start_value, double expected_value,
                     const AttLimits &limits, double step);
    ~FitParameterPlan();

    double m_start_value; //!< starting value of fit parameter
    double m_expected_value; //!< expected value to find in the fit
    AttLimits m_limits; //!< limits of fit parameter
    double m_step; //!< step of fit parameter
    double m_threshold; //!< threshold on found value
};

#endif
