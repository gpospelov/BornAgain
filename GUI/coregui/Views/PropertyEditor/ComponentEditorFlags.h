// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/ComponentEditorFlags.h
//! @brief     Defines class ComponentEditorFlags
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef COMPONENTEDITORFLAGS_H
#define COMPONENTEDITORFLAGS_H

#include "WinDllMacros.h"
#include <QObject>

class BA_CORE_API_ ComponentEditorFlags
{
public:
    enum EPresentationType {
        DEFAULT = 0x000,
        SHOW_DETAILED = 0x001,    // show whole item tree
        SHOW_CONDENSED = 0x002,   // show only items related to properties
        BROWSER_TABLE = 0x004,    // table-like browser
        BROWSER_GROUPBOX = 0x008, // groupbox-like browser
        BROWSER_BUTTON = 0x010    // button-like browser
    };
    Q_DECLARE_FLAGS(PresentationType, EPresentationType)

};

Q_DECLARE_OPERATORS_FOR_FLAGS(ComponentEditorFlags::PresentationType)


#endif
