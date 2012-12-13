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
    typedef ParameterPool::RealPar PoolParameter_t;
    typedef std::vector<PoolParameter_t > PoolParameterColl_t;

    FitParameterLinked();
    FitParameterLinked(const std::string &name, double value, double step, const AttLimits &attlim=AttLimits::limitless());
    virtual ~FitParameterLinked(){}

    //! set given value for all binded parameters
    virtual void setValue(double value)
    {
        FitParameter::setValue(value);
        for(PoolParameterColl_t::iterator it=m_parametercoll.begin(); it!=m_parametercoll.end(); ++it) {
            (*it).setValue(value); // setting value for all registered parameters
        }
    }

    //! add real parameter to the collection
    virtual void addParameter(PoolParameter_t par);

    //! add parameters from pool which match given wildcard
    virtual void addMatchedParametersFromPool(const ParameterPool *pool, const std::string &wildcard = std::string());

    //! print class
    friend std::ostream &operator<<(std::ostream &ostr, const FitParameterLinked &m) { m.print(ostr); return ostr; }

protected:
    // disabled copy constructor and assignment operator
    FitParameterLinked(const FitParameterLinked &other);
    FitParameterLinked &operator=(const FitParameterLinked &other);

    //! print class
    void print(std::ostream &ostr) const;

    PoolParameterColl_t m_parametercoll; //! collection of parameters from parameter pools
};

#endif // FITMULTIPARAMETER_H
