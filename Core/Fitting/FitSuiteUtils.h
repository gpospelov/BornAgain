// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuiteUtils.h
//! @brief     Defines namespace with utility functions for FitSuite.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSUITEUTILS_H
#define FITSUITEUTILS_H

#include "WinDllMacros.h"
#include <string>
#include <vector>

class FitParameterLinked;
class FitParameterSet;

namespace FitSuiteUtils {

//! Returns vector of linked parameters.
BA_CORE_API_ std::vector<FitParameterLinked*> linkedParameters(const FitParameterSet& fitParameters);

//! Returns multiline string representing linked sample parameters.
BA_CORE_API_ std::string linkToString(const FitParameterLinked& par);

//! Returns multiline string representing fit parameter definition.
BA_CORE_API_ std::string fitParameterSettingsToString(const FitParameterSet& fitParameters);

//! Validates all fit parameters for conflicts (steering same sample parameters).
BA_CORE_API_ bool hasConflicts(const FitParameterSet& fitParameters);


}

#endif
