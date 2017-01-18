// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitParameterLinked.h
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
#include <vector>

class ParameterPool;
class RealParameter;

//! Fittable parameter, linked to other parameters from pools.
//! @ingroup fitting_internal

class BA_CORE_API_ FitParameterLinked : public FitParameter
{
public:
    FitParameterLinked() {}
    FitParameterLinked(const std::string& pattern, double value,
                       const AttLimits& lim = AttLimits::limitless(), double step = 0.0);
    ~FitParameterLinked() final;

    FitParameterLinked* clone() const;

    void setValue(double value) final;

    FitParameterLinked& addPattern(const std::string& pattern);

    void addParameter(const RealParameter& par);

    void addMatchedParameters(const ParameterPool& pool);

    std::vector<std::string> patterns() const;

    std::vector<std::string> matchedParameterNames() const;

    std::vector<std::string> patternIntersection(const FitParameterLinked& other) const;

    bool isConflicting(const FitParameterLinked& other) const;

private:
    FitParameterLinked(const FitParameterLinked& other);
    bool isLinked(const RealParameter& newPar);
    std::vector<RealParameter*> m_pool_parameters; //!< linked parameters from pools
    std::vector<std::string> m_patterns;           //!< list of patterns to match from pool
};

#endif // FITPARAMETERLINKED_H
