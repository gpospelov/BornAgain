// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ParameterUtils.h
//! @brief     Defines namespace ParameterUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PARAMETERUTILS_H
#define PARAMETERUTILS_H

#include "Wrap/WinDllMacros.h"
#include <string>

class ParameterDistribution;
class ParticleDistribution;
class IParameterized;

namespace ParameterUtils
{

//! Returns true if given parameter name is related to angles.
BA_CORE_API_ bool isAngleRelated(const std::string& par_name);

//! Returns units of main parameter.
BA_CORE_API_ std::string mainParUnits(const ParticleDistribution& distr);

//! Returns units of main parameter.
BA_CORE_API_ std::string poolParameterUnits(const IParameterized& node, const std::string& parName);

} // namespace ParameterUtils

#endif // PARAMETERPATTERN_H
