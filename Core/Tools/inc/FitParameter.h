#ifndef FITPARAMETER_H
#define FITPARAMETER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FitParameter.h
//! @brief  Definition of FitParameter class
//! @author Scientific Computing Group at FRM II
//! @date   28.06.2012

#include "INamed.h"
#include <string>
#include <vector>


//- -------------------------------------------------------------------
//! @class FitParameter
//! @brief Parameter with value, error and limits for fitting routines
//- -------------------------------------------------------------------
class FitParameter : public INamed
{
public:
    FitParameter();
    FitParameter(const std::string &name, double value, double step, double error=0.0);
    FitParameter(const FitParameter &other);
    FitParameter &operator=(const FitParameter &other);
    virtual ~FitParameter(){}

    //! set value of parameter
    virtual void setValue(double value) { m_value = value;}
    //! get value of parameter
    virtual double getValue() const { return m_value;}

    //! set parameter step for minimizer
    virtual void setStep(double value) { m_step = value; }
    //! get parameter step for minimizer
    virtual double getStep() const { return m_step;}

    //! set lower and upper limits
    virtual void setLimits(double xmin, double xmax) { setLowerLimit(xmin); setUpperLimit(xmax); }

    //! set lower limit
    virtual void setLowerLimit(double value) { m_lower_limit = value; m_has_lower_limit = true; }
    //! get lower limit
    double getLowerLimit() const { return m_lower_limit; }

    //! set upper limit
    virtual void setUpperLimit(double value) { m_upper_limit = value; m_has_upper_limit = true; }
    //! get upper limit
    double getUpperLimit() const { return m_upper_limit; }

    //! if has lower limit
    virtual bool hasLowerLimit() const { return m_has_lower_limit; }

    //! if has upper limit
    virtual bool hasUpperLimit() const { return m_has_upper_limit; }

    //! if has upper limit
    virtual bool hasDoubleBound() const { return (m_has_lower_limit && m_has_upper_limit); }

    //! print class
    friend std::ostream &operator<<(std::ostream &ostr, const FitParameter &m) { m.print(ostr); return ostr; }

protected:
    //! print class
    void print(std::ostream &ostr) const;

    double m_value; //! parameter value
    double m_step;  //! parameter step size
    double m_error; //! parameter error
    bool   m_has_lower_limit; //! parameter has lower bound
    bool   m_has_upper_limit; //! parameter has upper bound
    double m_lower_limit; //! minimum allowed value
    double m_upper_limit; //! maximum allowed value
};


#endif // FITPARAMETER_H
