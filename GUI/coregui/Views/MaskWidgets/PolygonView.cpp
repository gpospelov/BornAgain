// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/PolygonView.cpp
//! @brief     Implements PolygonView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PolygonView.h"
#include "MaskEditorHelper.h"
#include "MaskItems.h"
#include <QPainter>
#include <QRectF>
#include <QDebug>

namespace {
const double bbox_margins = 5; // additional margins around points to form bounding box
}

PolygonView::PolygonView()
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable );
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

//    connect(this, SIGNAL(childrenChanged()), this, SLOT(update_view()));
}

void PolygonView::addView(IMaskView *childView, int row)
{
    Q_UNUSED(row);
    childView->setParentItem(this);
    connect(childView, SIGNAL(xChanged()), this, SLOT(update_view()));
    connect(childView, SIGNAL(yChanged()), this, SLOT(update_view()));

    //    childView->setVisible(false);
}

void PolygonView::onPropertyChange(const QString &propertyName)
{
    update_polygon();

}

void PolygonView::onChilderChanged()
{
    qDebug() << "PolygonView::onChilderChanged()";
//    update_polygon();

}

void PolygonView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    Q_ASSERT(m_item);
    painter->setRenderHints(QPainter::Antialiasing);
    prepareGeometryChange();
    bool mask_value = m_item->getRegisteredProperty(MaskItem::P_MASK_VALUE).toBool();
    painter->setBrush(MaskEditorHelper::getMaskBrush(mask_value));
    painter->setPen(MaskEditorHelper::getMaskPen(mask_value));
//    painter->drawRect(QRectF(0.0, 0.0, width(), height()));
//    painter->drawRect(m_bounding_rect);
//    QPolygon polygon;

//    // draws polygon
//    for (int i = 0; i < points.length(); ++i) {
//        polygon << QPointF;
//    }
//    painter->drawPolyline(polygon);

    painter->drawPolygon(m_polygon.toPolygon());

}

QVariant PolygonView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    qDebug() << "PolygonView::itemChange" << change;
    if(change == QGraphicsItem::ItemSelectedHasChanged) {
//        qDebug() << "PolygonView::itemChange -> selectedChange";
//        foreach(QGraphicsItem *childItem, childItems()) {
//            qDebug() << "AAAAA";
//            childItem->setVisible(this->isSelected());
//        }
    }
    return QGraphicsItem::itemChange(change, value);

}

void PolygonView::update_view()
{
    update_polygon();
}

void PolygonView::update_polygon()
{
    if(!m_item->childItemCount()) return;

    m_polygon.clear();

    foreach(QGraphicsItem *childItem, childItems()) {
        m_polygon << QPointF(childItem->x(), childItem->y());

    }


//    foreach(ParameterizedItem *item, m_item->childItems()) {
//        qreal px = toSceneX(item->getRegisteredProperty(PolygonPointItem::P_POSX).toReal());
//        qreal py = toSceneY(item->getRegisteredProperty(PolygonPointItem::P_POSY).toReal());
//        m_polygon << QPointF(px, py);
//    }

    m_bounding_rect = m_polygon.boundingRect().marginsAdded(QMarginsF(bbox_margins, bbox_margins,
                                                  bbox_margins, bbox_margins));

}

//void PolygonView::update_bounding_rect()
//{
//    m_bounding_rect = m_polygon.boundingRect().marginsAdded(QMarginsF(bbox_margins, bbox_margins,
//                                                  bbox_margins, bbox_margins));
//}

