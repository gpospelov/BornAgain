// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorActivity.h
//! @brief     Defines class MaskEditorActivity
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKEDITORACTIVITY_H
#define MASKEDITORACTIVITY_H

#include "WinDllMacros.h"
#include <QWidget>

//! Help class to define activities

class BA_CORE_API_ MaskEditorActivity
{
public:
    enum EActivityType {
        SELECTION_MODE      = 0x001,
        PAN_ZOOM_MODE       = 0x002,
        RECTANGLE_MODE      = 0x004,
        POLYGON_MODE        = 0x008,
        DRAWING_IN_PROGRESS = 0x010,
        MASK_GREEN_ID    = 0x020,
        MASK_RED_ID      = 0x040,
    };
Q_DECLARE_FLAGS(Flags, EActivityType)
};

Q_DECLARE_OPERATORS_FOR_FLAGS(MaskEditorActivity::Flags)

#endif
