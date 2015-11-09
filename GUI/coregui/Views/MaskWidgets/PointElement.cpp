// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/PointElement.cpp
//! @brief     Implements PointElement class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PointElement.h"
#include "MaskEditorHelper.h"
#include <QPainter>
#include<QGraphicsSceneHoverEvent>
#include <QDebug>

namespace {
QMap<PointElement::EPointType, Qt::CursorShape> create_cursors_map()
{
    QMap<PointElement::EPointType, Qt::CursorShape> result;
    result[PointElement::NONE] = Qt::ArrowCursor;
    result[PointElement::TOPLEFT] = Qt::SizeFDiagCursor;
    result[PointElement::TOPMIDDLE] = Qt::SizeVerCursor;
    result[PointElement::TOPRIGHT] = Qt::SizeBDiagCursor;
    result[PointElement::MIDDLERIGHT] = Qt::SizeHorCursor;
    result[PointElement::BOTTOMRIGHT] = Qt::SizeFDiagCursor;
    result[PointElement::BOTTOMMIDLE] = Qt::SizeVerCursor;
    result[PointElement::BOTTOMLEFT] = Qt::SizeBDiagCursor;
    result[PointElement::MIDDLELEFT] = Qt::SizeHorCursor;
    return result;
}
}

QMap<PointElement::EPointType, Qt::CursorShape> PointElement::m_cursors = create_cursors_map();

PointElement::PointElement(EPointType pointType, QGraphicsItem *parent)
    : QGraphicsObject(parent)
    , m_pointType(pointType)
{
    setAcceptHoverEvents(true);
    setCursor(m_cursors[m_pointType]);
//    connect(this, SIGNAL(parentChanged()), this, SLOT(onParentChanged()));
}

QRectF PointElement::boundingRect() const
{
    return QRectF(-4, -4, 8, 8);
}

void PointElement::onParentChanged()
{
    Q_ASSERT(0);
    set_position(parentItem()->boundingRect());
}

void PointElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing);
    prepareGeometryChange();

    painter->setBrush(MaskEditorHelper::getSelectionMarkerBrush());
    painter->setPen(MaskEditorHelper::getSelectionMarkerPen());
    painter->drawRect(boundingRect());

}

//! set position from point type
void PointElement::set_position(const QRectF &rect)
{
    if(m_pointType == TOPLEFT) {
        setPos(rect.topLeft());
    }

    else if(m_pointType == TOPMIDDLE) {
        setPos(QPointF(rect.x()+rect.width()/2., rect.y()));
    }

    else if(m_pointType == TOPRIGHT) {
        setPos(rect.topRight());
    }

    else if(m_pointType == MIDDLERIGHT) {
        setPos(QPointF(rect.x()+rect.width(), rect.y()+rect.height()/2.));
    }

    else if(m_pointType == BOTTOMRIGHT) {
        setPos(rect.bottomRight());
    }

    else if(m_pointType == BOTTOMMIDLE) {
        setPos(QPointF(rect.x()+rect.width()/2., rect.y()+rect.height()));
    }

    else if(m_pointType == BOTTOMLEFT) {
        setPos(rect.bottomLeft());
    }

    else if(m_pointType == MIDDLELEFT) {
        setPos(QPointF(rect.x(), rect.y()+rect.height()/2.));
    }
    qDebug() << "AAAAAA" << m_pointType << pos() << rect;

}

//void PointElement::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
//{
//    qDebug() << "PointElement::hoverMoveEvent";
//    setCursor(Qt::SizeBDiagCursor);
//}

