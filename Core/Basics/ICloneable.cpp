// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/ICloneable.cpp
//! @brief     Defines the interface ICloneable.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Basics/ICloneable.h"

// To emit vtable in this translation unit (see warning weak-vtables):
ICloneable::ICloneable() = default;
ICloneable::~ICloneable() = default;
