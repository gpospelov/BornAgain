#ifndef IINTENSITYFUNCTION_H
#define IINTENSITYFUNCTION_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IIntensityFunction.h
//! @brief  Definition of the functions to apply on intensities before doing any chi2 calculations
//! @author Scientific Computing Group at FRM II
//! @date   Jul 20, 2012

#include <cmath>

class IIntensityFunction
{
public:
    virtual ~IIntensityFunction() {}
    virtual IIntensityFunction *clone() const=0;

    virtual double evaluate(double value) const=0;

};

class IntensityFunctionLog : public IIntensityFunction
{
public:
    virtual ~IntensityFunctionLog() {}
    virtual IntensityFunctionLog *clone() const { return new IntensityFunctionLog(); }
    virtual inline double evaluate(double value) const { return (value > 0 ? std::log(value) : 0); }
};



#endif // IINTENSITYFUNCTION_H
