// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fitting/inc/AttFitting.h
//! @brief     Defines class AttFitting.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ATTFITTING_H
#define ATTFITTING_H

#include "WinDllMacros.h"
#include <iostream>
#include <iomanip>

//! General fitting attributes.

class BA_CORE_API_ AttFitting
{
 public:
    AttFitting();
    ~AttFitting(){}

    double getDerivEpsilon() const { return m_deriv_epsilon; }
    void setDerivEpsilon(double deriv_epsilon) { m_deriv_epsilon = deriv_epsilon; }

    double getStepFactor() const { return m_step_factor; }
    void setStepFactor(double step_factor) { m_step_factor = step_factor; }

 private:
    double m_deriv_epsilon;  //! epsilon for derivative calculation
    double m_step_factor; //! default relative parameter step
};

inline AttFitting::AttFitting()
    : m_deriv_epsilon(1e-09)
    , m_step_factor(0.01)
{
}

#endif // ATTFITTING_H


