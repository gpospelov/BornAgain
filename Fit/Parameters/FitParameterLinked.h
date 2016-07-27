// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/FitParameterLinked.h
//! @brief     Declares class FitParameterLinked.
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

#include "FitParameter.h" // inheriting from
#include "RealParameterWrapper.h"
#include <vector>

class ParameterPool;

//! @class FitParameterLinked
//! @ingroup fitting_internal
//! @brief Provide simultaneous access for several real parameters from parameter pool

class BA_CORE_API_ FitParameterLinked : public FitParameter
{
 public:
    FitParameterLinked();
    FitParameterLinked(const std::string& name, double value, double step,
                       const AttLimits& attlim=AttLimits::limitless(), double error=0.0);
    virtual ~FitParameterLinked(){}

    //! Sets given value for all bound parameters
    virtual void setValue(double value);

    //! Adds real parameter to the collection
    virtual void addParameter(RealParameterWrapper par);

    //! Adds parameters from pool which match given wildcard
    virtual void addMatchedParametersFromPool(
        const ParameterPool* pool, const std::string& wildcard = std::string());

    //! Prints class
    friend std::ostream& operator<<(std::ostream& ostr, const FitParameterLinked& m) {
        m.print(ostr); return ostr; }

 protected:
    //! Prints class
    void print(std::ostream& ostr) const;

    std::vector<RealParameterWrapper> m_pool_parameters; //! collection of parameters from parameter pools

 private:
    FitParameterLinked(const FitParameterLinked& );
    FitParameterLinked& operator=(const FitParameterLinked& );
};

#endif // FITPARAMETERLINKED_H
