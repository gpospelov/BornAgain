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
    FitParameter(const FitParameter &other);
    FitParameter &operator=(const FitParameter &other);
    virtual ~FitParameter(){}

    //! return value of parameter
    virtual double getValue() const { return m_value;}

    //! set value of parameter
    virtual void setValue(double value) { m_value = value;}

    //! print class
    friend std::ostream &operator<<(std::ostream &ostr, const FitParameter &m) { m.print(ostr); return ostr; }

protected:
    //! print class
    void print(std::ostream &ostr) const;

    double m_value; //! parameter value
    double m_error; //! parameter error
    double m_lower_limit; //! minimum allowed value
    double m_upper_limit; //! maximum allowed value
};

#endif // FITPARAMETER_H
