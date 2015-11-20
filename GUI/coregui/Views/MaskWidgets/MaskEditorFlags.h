// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorFlags.h
//! @brief     Defines class MaskEditorFlags
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKEDITORFLAGS_H
#define MASKEDITORFLAGS_H

#include "WinDllMacros.h"
#include <QWidget>

//! Help class to define various flags for MaskEditor operation

class BA_CORE_API_ MaskEditorFlags
{
public:
    enum EActivityType {
        SELECTION_MODE       = 0x0001,
        PAN_ZOOM_MODE        = 0x0002,
        RECTANGLE_MODE       = 0x0004,
        POLYGON_MODE         = 0x0010,
        VERTICAL_LINE_MODE   = 0x0020,
        HORIZONTAL_LINE_MODE = 0x0040,
        ELLIPSE_MODE         = 0x0080,
        MASKALL_MODE         = 0x0100,
        DRAWING_IN_PROGRESS  = 0x0200,
    };
    Q_DECLARE_FLAGS(Activity, EActivityType)

    enum EMoveType {
        BRING_TO_FRONT,
        SEND_TO_BACK
    };
    Q_DECLARE_FLAGS(Stacking, EMoveType)

    enum EMaskValue {
        MASK_OFF,
        MASK_ON
    };
    Q_DECLARE_FLAGS(MaskValue, EMaskValue)

};

Q_DECLARE_OPERATORS_FOR_FLAGS(MaskEditorFlags::Activity)
Q_DECLARE_OPERATORS_FOR_FLAGS(MaskEditorFlags::Stacking)
Q_DECLARE_OPERATORS_FOR_FLAGS(MaskEditorFlags::MaskValue)

#endif
