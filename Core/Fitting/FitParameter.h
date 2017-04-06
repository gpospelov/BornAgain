// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitParameter.h
//! @brief     Defines class FitParameter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITPARAMETER_H
#define FITPARAMETER_H

#include "IFitParameter.h"
#include <vector>

class ParameterPool;
class RealParameter;

//! Fittable parameter, linked to other parameters from pools.
//! @ingroup fitting_internal

class BA_CORE_API_ FitParameter : public IFitParameter
{
public:
    FitParameter() {}
    FitParameter(const std::string& pattern, double value,
                 const AttLimits& lim = AttLimits::limitless(), double step = 0.0);
    FitParameter(double value, const AttLimits& lim = AttLimits::limitless(), double step = 0.0);
    ~FitParameter() final;

    FitParameter* clone() const;

    void setValue(double value) final;

    FitParameter& addPattern(const std::string& pattern);

    void addParameter(const RealParameter& par);

    void addMatchedParameters(const ParameterPool& pool);

    std::vector<std::string> patterns() const;

    std::vector<std::string> matchedParameterNames() const;

    std::vector<std::string> patternIntersection(const FitParameter& other) const;

    bool isConflicting(const FitParameter& other) const;

private:
    FitParameter(const FitParameter& other);
    bool isLinked(const RealParameter& newPar);
    std::vector<RealParameter*> m_pool_parameters; //!< linked parameters from pools
    std::vector<std::string> m_patterns;           //!< list of patterns to match from pool
};

#endif // FITPARAMETER_H
