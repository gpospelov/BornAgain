// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/PropertyEditorFactory.h
//! @brief     Defines PropertyEditorFactory namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PROPERTYEDITORFACTORY_H
#define PROPERTYEDITORFACTORY_H

#include "WinDllMacros.h"

class QWidget;
class SessionItem;

//! Creates editors for SessionItem's values.

namespace PropertyEditorFactory
{

BA_CORE_API_ QWidget* CreateEditor(SessionItem& item, QWidget* parent = nullptr);

}

#endif  //  PROPERTYEDITORFACTORY_H
