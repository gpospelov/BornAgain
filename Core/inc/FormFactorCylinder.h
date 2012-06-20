#ifndef FORMFACTORCYLINDER_H
#define FORMFACTORCYLINDER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorCylinder.h
//! @brief  Definition of FormFactorCylinder
//! @author Scientific Computing Group at FRM II
//! @date   01.05.2012

#include "IFormFactor.h"
#include "IStochasticParameter.h"


class FormFactorCylinder : public IBornFormFactor
{
public:
    FormFactorCylinder(double height, double radius);
    FormFactorCylinder(StochasticParameter<double> *p_height, StochasticParameter<double> *p_radius);
    ~FormFactorCylinder();

    virtual int getNumberOfStochasticParameters() { return 2; }

protected:
    virtual complex_t evaluate_for_q(kvector_t q) const;
    virtual complex_t evaluate_for_complex_qz(kvector_t q, complex_t qz) const;

private:
    StochasticParameter<double> *mp_height;
    StochasticParameter<double> *mp_radius;
};

#endif // FORMFACTORCYLINDER_H
