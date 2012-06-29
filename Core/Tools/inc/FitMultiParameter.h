#ifndef FITMULTIPARAMETER_H
#define FITMULTIPARAMETER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FitMultiParameter.h
//! @brief  Definition of FitMultiParameter class
//! @author Scientific Computing Group at FRM II
//! @date   28.06.2012

#include "FitParameter.h"
#include "ParameterPool.h"
#include <string>
#include <vector>
#include <iostream>


//- -------------------------------------------------------------------
//! @class FitMultiParameter
//! @brief Provide simultaneous access for several real parameters from
//! parameter pool
//- -------------------------------------------------------------------
class FitMultiParameter : public FitParameter
{
public:
    typedef ParameterPool::RealPar parameter_t;
    typedef std::vector<parameter_t > parametercoll_t;

    FitMultiParameter();

    virtual void setValue(double value)
    {
        FitParameter::setValue(value);
        for(parametercoll_t::iterator it=m_parametercoll.begin(); it!=m_parametercoll.end(); it++) {
            (*it).setValue(value); // setting value for all registered parameters
        }
    }

    //! add real parameter to the collection
    virtual void addParameter(parameter_t par);

    //! add real parameter with given name from the pool to the collection of parameters
    virtual void addParameterFromPool(std::string parname, const ParameterPool *pool);

    //! add all real parameters which match given pattern ('*?' wildcards) to the collection of parameters
    virtual void addMatchedParametersFromPool(std::string wildcardPattern, const ParameterPool *pool);

    //! print class
    friend std::ostream &operator<<(std::ostream &ostr, const FitMultiParameter &m) { m.print(ostr); return ostr; }

protected:
    //! print class
    void print(std::ostream &ostr) const;

    parametercoll_t m_parametercoll;
};

#endif // FITMULTIPARAMETER_H
