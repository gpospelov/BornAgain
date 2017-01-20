// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Parameters/FitParameter.h
//! @brief     Defines class FitParameter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFITPARAMETER_H
#define IFITPARAMETER_H

#include "WinDllMacros.h"
#include "AttLimits.h"
#include <string>

//! A fittable parameter with value, error, step, and limits.
//! @ingroup fitting

class BA_CORE_API_ IFitParameter
{
public:
    IFitParameter();
    IFitParameter(const std::string& name, double value,
                 const AttLimits& limits=AttLimits::limitless(), double step=0.0);
    IFitParameter& operator=(const IFitParameter&) = delete;
    virtual ~IFitParameter(){}

    IFitParameter* clone() const;

    std::string name() const;
    IFitParameter& setName(const std::string& name);

    double startValue() const;
    void setStartValue(double value);

    double value() const;
    virtual void setValue(double value);

    virtual IFitParameter& addPattern(const std::string& pattern);

    double step() const;
    IFitParameter& setStep(double value);

    double error() const;
    void setError(double value);

    const AttLimits& limits() const;
    AttLimits& limits();

    IFitParameter& setLimits(const AttLimits& limits);
    IFitParameter& setLowerLimited(double bound_value);
    IFitParameter& setPositive();
    IFitParameter& setNonnegative();
    IFitParameter& setUpperLimited(double bound_value);
    IFitParameter& setLimited(double left_bound_value, double right_bound_value);
    IFitParameter& setFixed();

    virtual std::string toString() const;

protected:
    IFitParameter(const IFitParameter& other);

private:    
    std::string m_name;
    double m_start_value;
    double m_value;
    double m_step;
    double m_error;
    AttLimits m_limits;
};

#endif // IFITPARAMETER_H
