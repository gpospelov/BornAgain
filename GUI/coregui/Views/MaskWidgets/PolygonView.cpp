#include "PolygonView.h"
#include "ParameterizedItem.h"
#include "PolygonItem.h"
#include "PointItem.h"
#include <cmath>
#include <QDebug>
#include <QPainter>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>

PolygonView::PolygonView()
    : m_changeCornerMode(false), m_indexOfCurrentSelectedPoint(0), m_mouseIsOverFirstPoint(false)

{
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->cursor().setShape(Qt::ClosedHandCursor);
    this->setAcceptHoverEvents(true);
}

void PolygonView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen;
    prepareGeometryChange();
    painter->setRenderHints(QPainter::Antialiasing);
    QList<ParameterizedItem *> points = m_item->childItems();
    QPolygon polygon;

    // draws polygon
    for (int i = 0; i < points.length(); ++i) {
        polygon << QPoint(points[i]->getRegisteredProperty(PointItem::P_POSX).toReal(),
                          points[i]->getRegisteredProperty(PointItem::P_POSY).toReal());
    }
    painter->drawPolyline(polygon);

    // fills polygon with a color
    if (getFirstPoint().center().x() == polygon[polygon.length() - 1].x() && getFirstPoint().center().y() == polygon[polygon.length() - 1].y() && points.length() >= 2) {

        QPainterPath path;
        QBrush transRed(QColor(0xFF, 0, 0, 0x80));
        QBrush transBlue(QColor(0, 0, 0xFF, 0x80));
        path.moveTo(polygon[0].x(),polygon[0].y());
        for (int i = 1; i < polygon.length(); ++i) {
            path.lineTo(polygon[i].x(), polygon[i].y());
        }
        painter->setPen(Qt::NoPen);
        if (m_item->getRegisteredProperty(PolygonItem::P_COLOR).toInt() == 0) {
            painter->fillPath(path, transRed);
        } else {
            painter->fillPath(path, transBlue);
        }
    }

    if (points.length() >= 1
        && m_item->getRegisteredProperty(PolygonItem::P_DRAWINGMODE).toBool()) {
        pen.setWidth(1);
        if (m_mouseIsOverFirstPoint) {
            painter->fillRect(getFirstPoint(), Qt::red);
        } else {
            painter->drawRect(getFirstPoint());
        }
    }

    // paint corner rectangles only if this item is selected
    if (this->isSelected()) {
//        painter->setBrush(Qt::green);
//        painter->drawRect(getTopLeftCorner());
//        painter->drawRect(getBottomLeftCorner());
//        painter->drawRect(getTopRightCorner());
//        painter->drawRect(getBottomRightCorner());
    }
    // draw all points if item is finised with drawing and is selected
    if (!m_item->getRegisteredProperty(PolygonItem::P_DRAWINGMODE).toBool() && isSelected()) {
        pen.setWidth(5);
        painter->setPen(pen);
        for (int i = 0; i < points.length() - 1; ++i) {
            painter->drawPoint(
                QPointF(polygon[i].x(), polygon[i].y()));
        }
        painter->setPen(QPen());
    }
}

QRectF PolygonView::boundingRect() const
{
    if (m_item->childItems().length() >= 1) {
        return calculateBoundingRectangle();
    } else {
        return QRectF(0, 0, 20, 20);
    }
}

bool PolygonView::isCornerClicked(QGraphicsSceneMouseEvent *event)
{
    QList<ParameterizedItem *> points = m_item->childItems();
    for (int i = 0; i < points.length() - 1; ++i) {
        QRectF rectangle(
            points[i]->getRegisteredProperty(PointItem::P_POSX).toReal() - 2.5,
            points[i]->getRegisteredProperty(PointItem::P_POSY).toReal() - 2.5, 5, 5);
        if (rectangle.contains(event->pos())) {
            if (i != points.length() - 1 && i != 0) {
                m_indexOfCurrentSelectedPoint = i;
            } else {
                m_indexOfCurrentSelectedPoint = 0;
            }
            m_changeCornerMode = true;
            this->setFlag(QGraphicsItem::ItemIsMovable, false);
            return true;
        }
    }
    return false;
}

QRectF PolygonView::calculateBoundingRectangle() const
{
    QList<ParameterizedItem *> points = m_item->childItems();
    int smallestXValue = points[0]->getRegisteredProperty(PointItem::P_POSX).toReal();
    int biggestXValue = points[0]->getRegisteredProperty(PointItem::P_POSX).toReal();
    int smallestYValue = points[0]->getRegisteredProperty(PointItem::P_POSY).toReal();
    int biggestYValue = points[0]->getRegisteredProperty(PointItem::P_POSY).toReal();

    for (int i = 0; i < points.length(); ++i) {
        if (points[i]->getRegisteredProperty(PointItem::P_POSX).toReal() < smallestXValue) {
            smallestXValue = points[i]->getRegisteredProperty(PointItem::P_POSX).toReal();
        }
        if (points[i]->getRegisteredProperty(PointItem::P_POSX).toReal() > biggestXValue) {
            biggestXValue = points[i]->getRegisteredProperty(PointItem::P_POSX).toReal();
        }
        if (points[i]->getRegisteredProperty(PointItem::P_POSY).toReal() < smallestYValue) {
            smallestYValue = points[i]->getRegisteredProperty(PointItem::P_POSY).toReal();
        }
        if (points[i]->getRegisteredProperty(PointItem::P_POSY).toReal() > biggestYValue) {
            biggestYValue = points[i]->getRegisteredProperty(PointItem::P_POSY).toReal();
        }
    }
    return QRectF(QPointF(smallestXValue - 20, smallestYValue - 20),
                  QPointF(biggestXValue + 20, biggestYValue + 20));
}

void PolygonView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (isCornerClicked(event)) {
        m_changeCornerMode = true;
    } else if (event->button() == Qt::RightButton) {
        m_item->setRegisteredProperty(PolygonItem::P_DRAWINGMODE, false);
    } else {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mousePressEvent(event);
    }
}

void PolygonView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_changeCornerMode) {
        QList<ParameterizedItem *> points = m_item->childItems();
        setCursor(Qt::CrossCursor);
        if (m_indexOfCurrentSelectedPoint == 0) {
            points[m_indexOfCurrentSelectedPoint]->setRegisteredProperty(PointItem::P_POSX, event->pos().x());
            points[m_indexOfCurrentSelectedPoint]->setRegisteredProperty(PointItem::P_POSY, event->pos().y());
            points[points.length() - 1]->setRegisteredProperty(PointItem::P_POSX, event->pos().x());
            points[points.length() - 1]->setRegisteredProperty(PointItem::P_POSY, event->pos().y());
        } else {
            points[m_indexOfCurrentSelectedPoint]->setRegisteredProperty(PointItem::P_POSX, event->pos().x());
            points[m_indexOfCurrentSelectedPoint]->setRegisteredProperty(PointItem::P_POSY, event->pos().y());
        }
    } else if (!m_item->getRegisteredProperty(PolygonItem::P_DRAWINGMODE).toBool()) {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void PolygonView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    m_changeCornerMode = false;
    setCursor(Qt::ArrowCursor);
    QGraphicsItem::mouseReleaseEvent(event);
}

void PolygonView::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(getFirstPoint().contains(event->pos())) {
        m_mouseIsOverFirstPoint =  true;
    }
    else {
         m_mouseIsOverFirstPoint =  false;
    }
    QGraphicsItem::hoverMoveEvent(event);
}

void PolygonView::setInclude()
{
    m_item->setRegisteredProperty(PolygonItem::P_COLOR, 0);
}

//QRectF PolygonView::getTopLeftCorner()
//{
//    return QRectF(boundingRect().x(), boundingRect().y(), 10, 10);
//}

//QRectF PolygonView::getTopRightCorner()
//{
//    return QRectF(boundingRect().x() + boundingRect().width() - 10, boundingRect().y(), 10,
//                  10);
//}

//QRectF PolygonView::getBottomLeftCorner()
//{
//    return QRectF(boundingRect().x(), boundingRect().y() + boundingRect().height() - 10, 10, 10);
//}

//QRectF PolygonView::getBottomRightCorner()
//{
//    return QRectF(boundingRect().x() + boundingRect().width() - 10,
//                  boundingRect().y() + boundingRect().height() - 10, 10, 10);
//}

QRectF PolygonView::getFirstPoint() const
{
    QList<ParameterizedItem *> points = m_item->childItems();
    return QRectF(points[0]->getRegisteredProperty(PointItem::P_POSX).toReal() - 2.5,
                  points[0]->getRegisteredProperty(PointItem::P_POSY).toReal() - 2.5, 5, 5);
}

QPointF PolygonView::getLastPoint() const
{
    QList<ParameterizedItem *> points = m_item->childItems();
    int indexOfLastPoint = points.length() - 1;
    return QPointF(points[indexOfLastPoint]->getRegisteredProperty(PointItem::P_POSX).toReal(),
                   points[indexOfLastPoint]->getRegisteredProperty(PointItem::P_POSY).toReal());
}

ParameterizedItem *PolygonView::getParameterizedItem()
{
    return m_item;
}

void PolygonView::setParameterizedItem(ParameterizedItem *item)
{
    m_item = item;
    disconnect(this, SIGNAL(xChanged()), this, SLOT(onChangedX()));
    disconnect(this, SIGNAL(yChanged()), this, SLOT(onChangedY()));
    connect(m_item, SIGNAL(propertyChanged(QString)), this, SLOT(onPropertyChange(QString)));
}

void PolygonView::setExclude()
{
    m_item->setRegisteredProperty(PolygonItem::P_COLOR, 1);
}
