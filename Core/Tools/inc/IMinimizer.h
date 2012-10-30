#ifndef IMINIMIZER_H
#define IMINIMIZER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IMinimizer.h
//! @brief  Definition of Minimizer class
//! @author Scientific Computing Group at FRM II
//! @date   05.10.2012


#include "FitParameter.h"
#include <boost/function.hpp>


//- -------------------------------------------------------------------
//! @class IMinimizer
//! @brief Common interface for all kind minimizer's
//- -------------------------------------------------------------------
class IMinimizer
{
public:
    IMinimizer(){}
    virtual ~IMinimizer(){}

    //! set variable
    virtual void setVariable(int index, const FitParameter *par) = 0;

    //! set function to minimize
    virtual void setFunction(boost::function<double(const double *)> fcn, int ndim=1) = 0;

    //! run minimization
    virtual void minimize() = 0;

    //! get number of variables to fit
    virtual size_t getNumberOfVariables() const = 0;

    //! return minimum function value
    virtual double getMinValue() const = 0;

    //! return pointer to the parameters values at the minimum
    virtual double getValueOfVariableAtMinimum(size_t i) const = 0;

    //! return pointer to the parameters values at the minimum
    virtual double getErrorOfVariable(size_t i) const = 0;

    //! print fit results
    virtual void printResults() const = 0;

};

#endif // IMINIMIZER_H
