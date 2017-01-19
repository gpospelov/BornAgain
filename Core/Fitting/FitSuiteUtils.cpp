// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuiteUtils.cpp
//! @brief     Implements utility functions for FitSuite.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitSuiteUtils.h"
#include "FitParameter.h"
#include "FitParameterSet.h"
#include <boost/format.hpp>
#include <sstream>

std::vector<FitParameter*>
FitSuiteUtils::linkedParameters(const FitParameterSet& fitParameters)
{
    std::vector<FitParameter*> result;
    for(auto par : fitParameters) {
        if(FitParameter *linked = dynamic_cast<FitParameter*>(par))
            result.push_back(linked);
        else
            throw std::runtime_error("FitSuiteUtils::linkedParameters() -> Error. Can't cast");
    }

    return result;
}

std::string FitSuiteUtils::linkToString(const FitParameter& par)
{
    std::ostringstream result;

    result << boost::format("%-10s : '%-s'\n") % "name" % par.name();
    result << boost::format("%-10s : ") % "pattern";
    size_t index(0);
    for(auto pattern : par.patterns()) {
        result << "'" << pattern << "'";
        ++index;
        if(index!= par.patterns().size())
            result << ", ";
    }
    result << std::endl;

    for(auto link : par.matchedParameterNames())
        result << boost::format("%-10s : '%s'\n") % "linked to" % link;

    return result.str();
}

std::string FitSuiteUtils::fitParameterSettingsToString(const FitParameterSet& fitParameters)
{
    std::ostringstream result;
    size_t index(0);
    auto parameters = FitSuiteUtils::linkedParameters(fitParameters);
    for(auto par : parameters) {
        result << FitSuiteUtils::linkToString(*par);
        ++index;
        if(index != parameters.size())
            result << std::endl;
    }

    return result.str();
}

bool FitSuiteUtils::hasConflicts(const FitParameterSet& fitParameters)
{
    std::vector<FitParameter*> parameters = FitSuiteUtils::linkedParameters(fitParameters);
    for(auto par1 : parameters) {
        for(auto par2 : parameters) {
            if(par1 != par2)
                if(par1->isConflicting(*par2))
                    return true;
        }
    }

    return false;
}
