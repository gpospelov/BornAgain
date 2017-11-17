// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentUtis.h
//! @brief     Defines ComponentUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COMPONENTUTILS_H
#define COMPONENTUTILS_H

#include "WinDllMacros.h"
#include <QStringList>

//! Contains collection of utility functions to support editing of SessionItem's components.

namespace ComponentUtils
{

//! Returns list of strings representing modelTypes suitable for editing in component editors.
BA_CORE_API_ QStringList propertyRelatedTypes();

}

#endif
