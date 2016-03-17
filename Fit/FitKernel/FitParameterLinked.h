// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/FitParameterLinked.h
//! @brief     Defines class FitParameterLinked.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITPARAMETERLINKED_H
#define FITPARAMETERLINKED_H

#include "FitParameter.h"
#include "ParameterPool.h"
#include "AttLimits.h"
#include <string>
#include <vector>
#include <iostream>


//! @class FitParameterLinked
//! @ingroup fitting_internal
//! @brief Provide simultaneous access for several real parameters from parameter pool

class BA_CORE_API_ FitParameterLinked : public FitParameter
{
 public:
    typedef std::vector<ParameterPool::parameter_t > pool_parameters_t;

    FitParameterLinked();
    FitParameterLinked(const std::string& name, double value, double step, const AttLimits& attlim=AttLimits::limitless(), double error=0.0);
    virtual ~FitParameterLinked(){}

    //! Sets given value for all binded parameters
    virtual void setValue(double value) {
        FitParameter::setValue(value);
        for(pool_parameters_t::iterator it=m_pool_parameters.begin(); it!=m_pool_parameters.end(); ++it) {
            (*it).setValue(value);
        }
    }

    //! Adds real parameter to the collection
    virtual void addParameter(ParameterPool::parameter_t par);

    //! Adds parameters from pool which match given wildcard
    virtual void addMatchedParametersFromPool(const ParameterPool *pool, const std::string& wildcard = std::string());

    //! Prints class
    friend std::ostream& operator<<(std::ostream& ostr, const FitParameterLinked& m) { m.print(ostr); return ostr; }

 protected:
    //! Prints class
    void print(std::ostream& ostr) const;

    pool_parameters_t m_pool_parameters; //! collection of parameters from parameter pools

 private:
    FitParameterLinked(const FitParameterLinked& );
    FitParameterLinked& operator=(const FitParameterLinked& );
};

#endif // FITPARAMETERLINKED_H


