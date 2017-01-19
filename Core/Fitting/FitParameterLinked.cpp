// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitParameterLinked.cpp
//! @brief     Implements class FitParameterLinked.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitParameterLinked.h"
#include "ParameterPool.h"
#include "RealParameter.h"
#include <stdexcept>
#include <algorithm>
#include <set>
#include <sstream>
#include <iterator>

FitParameterLinked::FitParameterLinked(const std::string& pattern, double value,
                                       const AttLimits& lim, double step)
    : FitParameter("noname", value, lim, step)
{
    addPattern(pattern);
}

FitParameterLinked::~FitParameterLinked()
{
    for (auto* par : m_pool_parameters)
        delete par;
}

FitParameterLinked* FitParameterLinked::clone() const
{
    return new FitParameterLinked(*this);
}

//! Sets given value for all bound parameters

void FitParameterLinked::setValue(double value)
{
    FitParameter::setValue(value);
    for (auto* par : m_pool_parameters)
        par->setValue(value);
}

//! Adds pattern to the list for later usage in parameter pool matching.

FitParameterLinked& FitParameterLinked::addPattern(const std::string& pattern)
{
    if (std::find(m_patterns.begin(), m_patterns.end(), pattern) != m_patterns.end())
        throw std::runtime_error("FitParameterLinked::addPattern() -> Error. Already contain '"
                                 + pattern + "'.");
    m_patterns.push_back(pattern);
    return *this;
}

//! Adds real parameter to the collection

void FitParameterLinked::addParameter(const RealParameter& par)
{
    if (par.isNull())
        throw std::runtime_error("FitParameterLinked::addParameter() -> Error. "
                                 "Attempt to add null parameter.");
    m_pool_parameters.push_back(par.clone());
}

//! Adds parameters from pool which match given wildcard

void FitParameterLinked::addMatchedParameters(const ParameterPool& pool)
{
    for (auto wildcard : m_patterns) {
        for (auto par : pool.getMatchedParameters(wildcard)) {
            if(!isLinked(*par))
                m_pool_parameters.push_back(par->clone());
        }
        if (m_pool_parameters.empty())
            throw std::runtime_error("FitParameterLinked::addMatchedParameters() -> Error! "
                                     "Failed to add anything from pool using wildcard '"
                                     + wildcard + "'");
    }
}

std::vector<std::string> FitParameterLinked::patterns() const
{
    return m_patterns;
}

//! Returns vector of strings with names of all matched parameters.

std::vector<std::string> FitParameterLinked::matchedParameterNames() const
{
    std::vector<std::string> result;
    std::transform(m_pool_parameters.begin(), m_pool_parameters.end(), std::back_inserter(result),
                   [](RealParameter* par){return par->getName();});
    return result;
}

//! Returns vector containing patterns existing in both FitParametersLinked.

std::vector<std::string>
FitParameterLinked::patternIntersection(const FitParameterLinked& other) const
{
    std::set<std::string> set1(m_patterns.begin(), m_patterns.end());
    std::set<std::string> set2(other.m_patterns.begin(), other.m_patterns.end());
    std::vector<std::string> intersection;
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
                          std::back_inserter(intersection));
    return intersection;
}

//! Returns true if two FitParameterLinked are intended to steer same RealParameter.

bool FitParameterLinked::isConflicting(const FitParameterLinked& other) const
{
    if(patternIntersection(other).size())
        return true;

    // analyze two pool of parameters and check if they are conflicting
    bool isConflicting(false);
    for (auto par1 : m_pool_parameters) {
        for_each(other.m_pool_parameters.begin(), other.m_pool_parameters.end(),
            [&](RealParameter* par2) { if (par1->hasSameData(*par2)) isConflicting = true;});
    }
    return isConflicting;
}

FitParameterLinked::FitParameterLinked(const FitParameterLinked& other)
    : FitParameter(other)
{
    for (auto par : other.m_pool_parameters)
        m_pool_parameters.push_back(par->clone());
    m_patterns = other.m_patterns;
}

//! Returns true if clone of given RealParameter was already added.

bool FitParameterLinked::isLinked(const RealParameter& newPar)
{
    for (auto par : m_pool_parameters) {
        if(par->getName() == newPar.getName() && par->hasSameData(newPar))
            return true;

        if(par->getName() != newPar.getName() && par->hasSameData(newPar))
            throw std::runtime_error("FitParameterLinked::isLinked() -> Error. Different "
                                     "parameter with same data.");

        if(par->getName() == newPar.getName() && !par->hasSameData(newPar))
            throw std::runtime_error("FitParameterLinked::isLinked() ->Error. Same parameter "
                                     "name with different data.");
    }

    return  false;
}
