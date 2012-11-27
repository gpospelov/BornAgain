#ifndef ISQUAREDFUNCTION_H_
#define ISQUAREDFUNCTION_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ISquaredFunction.h
//! @brief  Definition of function to calculate squared difference
//! @author Scientific Computing Group at FRM II
//! @date   Jul 20, 2012

#include "Numeric.h"

#include <cmath>
#include <iostream>


class ISquaredFunction
{
public:
    virtual ~ISquaredFunction() {}
    virtual ISquaredFunction *clone() const=0;

    virtual double calculateSquaredDifference(double real_value, double simulated_value) const=0;
};


class SquaredFunctionDefault : public ISquaredFunction
{
public:
    SquaredFunctionDefault() {}
    virtual ~SquaredFunctionDefault() {}
    virtual SquaredFunctionDefault *clone() const { return new SquaredFunctionDefault(); }

    virtual inline double calculateSquaredDifference(double real_value, double simulated_value) const
    {
        double diff_squared = (simulated_value-real_value)*(simulated_value-real_value);
        if (diff_squared < Numeric::double_epsilon) {
            return 0.0;
        }
        double sigma = std::max(real_value,1.0);
        return diff_squared/sigma;
    }
};


class SquaredFunctionWhichOnlyWorks : public ISquaredFunction
{
public:
    SquaredFunctionWhichOnlyWorks() {}
    virtual ~SquaredFunctionWhichOnlyWorks() {}
    virtual SquaredFunctionWhichOnlyWorks *clone() const { return new SquaredFunctionWhichOnlyWorks(*this); }

    virtual inline double calculateSquaredDifference(double real_value, double simulated_value) const
    {
        double diff_squared = (simulated_value-real_value)*(simulated_value-real_value);
        if (diff_squared < Numeric::double_epsilon) {
            return 0.0;
        }
        double sigma1 = std::max(real_value,1.0);
        double sigma2 = std::max(simulated_value,1.0);
        double sigma = std::sqrt(sigma1*sigma1 + sigma2*sigma2);
        double normalization = sigma;
        return diff_squared/normalization;
    }
};


class SquaredFunctionWithSystematicError : public ISquaredFunction
{
public:
    SquaredFunctionWithSystematicError(double epsilon = 0.08) : m_epsilon(epsilon){}
    virtual ~SquaredFunctionWithSystematicError() {}
    virtual SquaredFunctionWithSystematicError *clone() const { return new SquaredFunctionWithSystematicError(*this); }

    virtual inline double calculateSquaredDifference(double real_value, double simulated_value) const
    {
        double diff_squared = (simulated_value-real_value)*(simulated_value-real_value);
        double sigma_squared = std::fabs(real_value) + (m_epsilon*real_value)*(m_epsilon*real_value);
        sigma_squared = std::max(sigma_squared, 1.0);
        return diff_squared/sigma_squared;
    }
private:
    double m_epsilon;
};


#endif /* ISQUAREDFUNCTION_H_ */
