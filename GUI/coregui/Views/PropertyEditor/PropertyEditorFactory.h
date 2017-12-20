// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/PropertyEditorFactory.h
//! @brief     Defines PropertyEditorFactory namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PROPERTYEDITORFACTORY_H
#define PROPERTYEDITORFACTORY_H

#include "WinDllMacros.h"
#include <QString>

class QWidget;
class SessionItem;
class QVariant;

//! Creates editors for SessionItem's values.

namespace PropertyEditorFactory
{

//! Returns true if the variant is one of our custom ones.
BA_CORE_API_ bool IsCustomVariant(const QVariant& variant);

//! Converts custom variant to string representation.
BA_CORE_API_ QString ToString(const QVariant& variant);

//! Creates an editor suitable for editing of item.value()
BA_CORE_API_ QWidget* CreateEditor(const SessionItem& item, QWidget* parent = nullptr);

}

#endif  //  PROPERTYEDITORFACTORY_H
