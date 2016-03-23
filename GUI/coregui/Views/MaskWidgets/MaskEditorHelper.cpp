// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorHelper.cpp
//! @brief     Implements class MaskEditorHelper
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaskEditorHelper.h"
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QRectF>

QBrush MaskEditorHelper::getSelectionMarkerBrush()
{
    QBrush result;
    result.setStyle(Qt::SolidPattern);
    result.setColor(QColor(226, 235, 244));
    return result;
}

QPen MaskEditorHelper::getSelectionMarkerPen()
{
    return QPen(QColor(99, 162, 217));
}

QBrush MaskEditorHelper::getMaskBrush(bool mask_value)
{
    QBrush result;
    result.setStyle(Qt::SolidPattern);
    if(mask_value) {
        result.setColor(QColor(209, 109, 97)); // deep red
    } else {
        result.setColor(QColor(0, 213, 106)); // deep green
    }
    return result;
}

QPen MaskEditorHelper::getMaskPen(bool mask_value)
{
    if(mask_value) {
        return QPen(QColor(165, 80, 76)); // dark red
    } else {
        return QPen(QColor(0, 140, 70)); // dark green
    }
}

QRectF MaskEditorHelper::getMarkerRectangle(const QPointF &pos)
{
    QRectF result(0, 0, 7, 7);
    result.moveCenter(pos);
    return result;
}
