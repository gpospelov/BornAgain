// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Fitting/FitParameter.h 
//! @brief     Defines class FitParameter.
//
// ************************************************************************** //

#ifndef FITPARAMETER_H
#define FITPARAMETER_H

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
    FitParameter(const std::string &name, double value, double step=0.0, const AttLimits &limits=AttLimits::limitless(), double error=0.0);
    virtual ~FitParameter(){}

    //! set value of parameter
    virtual void setValue(double value) { m_value = value;}
    //! get value of parameter
    virtual double getValue() const { return m_value;}

    //! set parameter step for minimizer
    virtual void setStep(double value) { m_step = value; }
    //! get parameter step for minimizer
    virtual double getStep() const { return m_step;}

    //! set parameter error
    virtual void setError(double value) { m_error = value; }
    //! get parameter step for minimizer
    virtual double getError() const { return m_error;}

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
