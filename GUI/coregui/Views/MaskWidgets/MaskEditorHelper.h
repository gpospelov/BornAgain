// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorHelper.h
//! @brief     Defines class MaskEditorHelper
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKEDITORHELPER_H
#define MASKEDITORHELPER_H

#include "WinDllMacros.h"
#include <QGraphicsItem>

class QBrush;
class QPen;
class QRectF;
class QPointF;

//! Static class to provide MaskEditor with common settings (colors, gradients, etc)

class BA_CORE_API_ MaskEditorHelper
{
public:
    enum EViewTypes {
        IMASKVIEW = QGraphicsItem::UserType+1, // = 65537
        RECTANGLE,
        SIZEHANDLE,
        POLYGON,
        POLYGONPOINT,
        VERTICALLINE,
        HORIZONTALLINE,
        ELLIPSE,
        MASKALL,
        MASKGRAPHICSPROXY
    };

    static QBrush getSelectionMarkerBrush();
    static QPen getSelectionMarkerPen();
    static QBrush getMaskBrush(bool mask_value);
    static QPen getMaskPen(bool mask_value);
    static QRectF getMarkerRectangle(const QPointF &pos);
};


#endif

