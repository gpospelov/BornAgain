#ifndef IRESOLUTIONFUNCTION2D_H_
#define IRESOLUTIONFUNCTION2D_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IResolutionFunction2D.h
//! @brief  Definition of IResolutionFunction2D interface
//! @author Scientific Computing Group at FRM II
//! @date   Oct 16, 2012

#include "IParameterized.h"

class IResolutionFunction2D : public IParameterized
{
public:
    virtual ~IResolutionFunction2D() {}

    virtual double evaluateCDF(double x, double y) const=0;
};

#endif /* IRESOLUTIONFUNCTION2D_H_ */
