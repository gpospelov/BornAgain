// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/ISquaredFunction.h
//! @brief     Defines classes ISquaredFunction, SquaredFunctionDefault, ...
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef ISQUAREDFUNCTION_H_
#define ISQUAREDFUNCTION_H_

#include "Numeric.h"
#include "Exceptions.h"

#include <iostream>

//! ?

class ISquaredFunction
{
public:
    virtual ~ISquaredFunction() {}
    virtual ISquaredFunction *clone() const=0;

    virtual double calculateSquaredDifference(double real_value, double simulated_value) const=0;
    virtual double calculateSquaredError(double real_value, double simulated_value = 0.0) const { (void)real_value; (void)simulated_value; throw NotImplementedException("ISquaredFunction::calculateError() -> Error! Not implemented."); }
};

//! ?

class SquaredFunctionDefault : public ISquaredFunction
{
public:
    SquaredFunctionDefault() {}
    virtual ~SquaredFunctionDefault() {}
    virtual SquaredFunctionDefault *clone() const { return new SquaredFunctionDefault(); }

    virtual double calculateSquaredDifference(double real_value, double simulated_value) const
    {
        double diff_squared = (simulated_value-real_value)*(simulated_value-real_value);
        if (diff_squared < Numeric::double_epsilon) {
            return 0.0;
        }
        double sigma_squared = std::max(real_value,1.0);
        return diff_squared/sigma_squared;
    }

    virtual double calculateSquaredError(double real_value, double /* simulated_value */) const
    {
        return std::max(real_value,1.0);
    }

};

//! ?

class SquaredFunctionWhichOnlyWorks : public ISquaredFunction
{
public:
    SquaredFunctionWhichOnlyWorks() {}
    virtual ~SquaredFunctionWhichOnlyWorks() {}
    virtual SquaredFunctionWhichOnlyWorks *clone() const { return new SquaredFunctionWhichOnlyWorks(*this); }

    virtual double calculateSquaredDifference(double real_value, double simulated_value) const
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

//! ?

class SquaredFunctionWithSystematicError : public ISquaredFunction
{
public:
    SquaredFunctionWithSystematicError(double epsilon = 0.08) : m_epsilon(epsilon){}
    virtual ~SquaredFunctionWithSystematicError() {}
    virtual SquaredFunctionWithSystematicError *clone() const { return new SquaredFunctionWithSystematicError(*this); }

    virtual double calculateSquaredDifference(double real_value, double simulated_value) const
    {
        double diff_squared = (simulated_value-real_value)*(simulated_value-real_value);
        return diff_squared/calculateSquaredError(real_value);
    }
    virtual double calculateSquaredError(double real_value, double simulated_value  = 0.0) const
    {
        (void)simulated_value;
        return std::max(std::fabs(real_value) + (m_epsilon*real_value)*(m_epsilon*real_value),1.0);
    }

private:
    double m_epsilon;
};

//! ?

class SquaredFunctionWithGaussianError : public ISquaredFunction
{
public:
    SquaredFunctionWithGaussianError(double sigma = 0.01) : m_sigma(sigma){}
    virtual ~SquaredFunctionWithGaussianError() {}
    virtual SquaredFunctionWithGaussianError *clone() const { return new SquaredFunctionWithGaussianError(*this); }

    virtual double calculateSquaredDifference(double real_value, double simulated_value) const
    {
        double diff_squared = (simulated_value-real_value)*(simulated_value-real_value);
        double sigma_squared = m_sigma*m_sigma;
        return diff_squared/sigma_squared;
    }
    virtual double calculateSquaredError(double /* real_value */, double /* simulated_value */) const
    {
        return m_sigma*m_sigma;
    }

private:
    double m_sigma;
};

#endif /* ISQUAREDFUNCTION_H_ */
