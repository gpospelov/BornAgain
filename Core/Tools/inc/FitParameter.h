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
#include "AttLimits.h"
#include <string>
#include <vector>


//- -------------------------------------------------------------------
//! @class FitParameter
//! @brief Parameter with value, error and limits for fitting routines
//- -------------------------------------------------------------------
class FitParameter : public INamed, public AttLimits
{
public:
    FitParameter();
    FitParameter(const AttLimits &limits);
    FitParameter(const std::string &name, double value, double step=0.0, const AttLimits &limits=AttLimits::limitless());
//    FitParameter(const FitParameter &other);
//    FitParameter &operator=(const FitParameter &other);
    virtual ~FitParameter(){}

    //! set value of parameter
    virtual void setValue(double value) { m_value = value;}
    //! get value of parameter
    virtual double getValue() const { return m_value;}

    //! set parameter step for minimizer
    virtual void setStep(double value) { m_step = value; }
    //! get parameter step for minimizer
    virtual double getStep() const { return m_step;}

    //! print class
    friend std::ostream &operator<<(std::ostream &ostr, const FitParameter &m) { m.print(ostr); return ostr; }

protected:
    //! print class
    void print(std::ostream &ostr) const;

    double m_value; //! parameter value
    double m_step;  //! parameter step size
    double m_error; //! parameter error
};


#endif // FITPARAMETER_H
