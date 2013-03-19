// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Fitting/AttFitting.h 
//! @brief     Defines class AttFitting.
//
// ************************************************************************** //

#ifndef ATTFITTING_H
#define ATTFITTING_H

#include <iostream>
#include <iomanip>

//- -------------------------------------------------------------------
//! @class AttFitting
//! @brief Defines general fitting attributes
//- -------------------------------------------------------------------
class AttFitting
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
