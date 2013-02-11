#ifndef ATTFITTING_H
#define ATTFITTING_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   AttFitting.h
//! @brief  Definition of AttFitting class
//! @author Scientific Computing Group at FRM II
//! @date   06.02.2013

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
