// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskEditorHelper.h
//! @brief     Defines class MaskEditorHelper
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
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
        RECTANGLEBASE,
        RECTANGLE,
        SIZEHANDLE,
        POLYGON,
        POLYGONPOINT,
        VERTICALLINE,
        HORIZONTALLINE,
        ELLIPSE,
        MASKALL,
        REGIONOFINTEREST,
        MASKGRAPHICSPROXY
    };

    static QBrush getSelectionMarkerBrush();
    static QPen getSelectionMarkerPen();
    static QBrush getMaskBrush(bool mask_value);
    static QPen getMaskPen(bool mask_value);
    static QRectF getMarkerRectangle(const QPointF &pos);
};


#endif // MASKEDITORHELPER_H

