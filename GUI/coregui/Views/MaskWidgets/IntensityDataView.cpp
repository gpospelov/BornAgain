// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/ClipView.cpp
//! @brief     Implements ClipView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IntensityDataView.h"
#include "ISceneAdaptor.h"
#include <QPainter>
#include <QBrush>
#include <QStyleOptionGraphicsItem>
#include <QDebug>


IntensityDataView::IntensityDataView()
{
    // the key flag to not to draw children going outside ot given shape
    setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
}

void IntensityDataView::update_view()
{
    m_bounding_rect = m_adaptor->getViewportRectangle();
    update();
    qDebug() << "AAA" << childItems();
}

void IntensityDataView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing);
    prepareGeometryChange();

//    QPolygonF clip_polygon = mapFromScene(m_adaptor->getViewportRectangle());
//    painter->setClipRegion(QRegion(clip_polygon.toPolygon()));


//    QColor color(250, 250, 240, 150);
//    painter->setBrush(color);
////    painter->setPen(MaskEditorHelper::getMaskPen(mask_value));
//    painter->drawRect(m_bounding_rect);

//    if(isSelected()) {
//        QPen pen;
//        pen.setStyle(Qt::DashLine);
//        painter->setPen(pen);
//        painter->setBrush(Qt::NoBrush);
//        painter->drawRect(m_bounding_rect);
//    }


}
