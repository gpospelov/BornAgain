// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/Unit.cpp
//! @brief     Implements class Unit.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Parametrization/Unit.h"
#include "Core/Basics/BornAgainNamespace.h"
#include <stdexcept>

void Unit::setUnit(const std::string& name)
{
    setName(name);
}
