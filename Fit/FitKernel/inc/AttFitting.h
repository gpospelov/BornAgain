// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/AttFitting.h
//! @brief     Defines class AttFitting.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ATTFITTING_H
#define ATTFITTING_H

#include "WinDllMacros.h"
#include <iostream>
#include <iomanip>


//! @class AttFitting
//! @ingroup fitting
//! @brief General fitting attributes.

class BA_CORE_API_ AttFitting
{
 public:
    AttFitting();
    ~AttFitting(){}

    double getDerivEpsilon() const;
    void setDerivEpsilon(double deriv_epsilon);

    double getStepFactor() const;
    void setStepFactor(double step_factor);

 private:
    double m_deriv_epsilon;  //! epsilon for derivative calculation
    double m_step_factor; //! default relative parameter step
    bool m_override_detector_axes; //! Experimental data will override
};

inline AttFitting::AttFitting()
    : m_deriv_epsilon(1e-09)
    , m_step_factor(0.01)
{
}

inline double AttFitting::getDerivEpsilon() const
{
    return m_deriv_epsilon;
}

inline void AttFitting::setDerivEpsilon(double deriv_epsilon)
{
    m_deriv_epsilon = deriv_epsilon;
}

inline double AttFitting::getStepFactor() const
{
    return m_step_factor;
}

inline void AttFitting::setStepFactor(double step_factor)
{
    m_step_factor = step_factor;
}



#endif // ATTFITTING_H


