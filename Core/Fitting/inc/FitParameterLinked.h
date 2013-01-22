#ifndef FITPARAMETERLINKED_H
#define FITPARAMETERLINKED_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FitParameterLinked.h
//! @brief  Definition of FitParameterLinked class
//! @author Scientific Computing Group at FRM II
//! @date   28.06.2012

#include "FitParameter.h"
#include "ParameterPool.h"
#include "AttLimits.h"
#include <string>
#include <vector>
#include <iostream>


//- -------------------------------------------------------------------
//! @class FitParameterLinked
//! @brief Provide simultaneous access for several real parameters from
//! parameter pool
//- -------------------------------------------------------------------
class FitParameterLinked : public FitParameter
{
public:
    typedef std::vector<ParameterPool::parameter_t > pool_parameters_t;

    FitParameterLinked();
    FitParameterLinked(const std::string &name, double value, double step, const AttLimits &attlim=AttLimits::limitless(), double error=0.0);
    virtual ~FitParameterLinked(){}

    //! set given value for all binded parameters
    virtual void setValue(double value) {
        FitParameter::setValue(value);
        for(pool_parameters_t::iterator it=m_pool_parameters.begin(); it!=m_pool_parameters.end(); ++it) {
            (*it).setValue(value);
        }
    }

    //! add real parameter to the collection
    virtual void addParameter(ParameterPool::parameter_t par);

    //! add parameters from pool which match given wildcard
    virtual void addMatchedParametersFromPool(const ParameterPool *pool, const std::string &wildcard = std::string());

    //! print class
    friend std::ostream &operator<<(std::ostream &ostr, const FitParameterLinked &m) { m.print(ostr); return ostr; }

protected:
    //! print class
    void print(std::ostream &ostr) const;

    pool_parameters_t m_pool_parameters; //! collection of parameters from parameter pools

private:
    FitParameterLinked(const FitParameterLinked &);
    FitParameterLinked &operator=(const FitParameterLinked &);
};

#endif // FITMULTIPARAMETER_H
