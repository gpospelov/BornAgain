
#include "PolygonView.h"
#include "ParameterizedItem.h"
#include "PolygonItem.h"
#include "PointItem.h"
#include <iostream>
#include <cmath>

PolygonView::PolygonView()
    : m_firstPoint(QRectF()), m_changeCornerMode(false), m_corner(NONE), m_currentPoint1(0),
      m_currentPoint2(0)

{
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    this->cursor().setShape(Qt::ClosedHandCursor);
    this->setAcceptHoverEvents(true);
    m_width = 100;
    m_heigth = 100;
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
        polygon << QPoint(points[i]->getRegisteredProperty(PointItem::P_POSX).toInt(),
                          points[i]->getRegisteredProperty(PointItem::P_POSY).toInt());
    }
    painter->drawPolyline(polygon);

    // fills polygon with a color
    if (getFirstPoint().contains(getLastPoint()) && points.length() >= 2) {

        QPainterPath path;
        QBrush transRed(QColor(0xFF, 0, 0, 0x80));
        QBrush transBlue(QColor(0, 0, 0xFF, 0x80));
        path.moveTo(points[0]->getRegisteredProperty(PointItem::P_POSX).toReal(),
                    points[0]->getRegisteredProperty(PointItem::P_POSY).toReal());
        for (int i = 1; i < points.length() - 1; ++i) {
            path.lineTo(points[i]->getRegisteredProperty(PointItem::P_POSX).toReal(),
                        points[i]->getRegisteredProperty(PointItem::P_POSY).toReal());
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
        m_item->setRegisteredProperty(PolygonItem::P_FIRSTPOINTXVALUE,
                                      points[0]->getRegisteredProperty(PointItem::P_POSX));
        m_item->setRegisteredProperty(PolygonItem::P_FIRSTPOINTYVALUE,
                                      points[0]->getRegisteredProperty(PointItem::P_POSY));
        if (m_item->getRegisteredProperty(PolygonItem::P_MOUSEISOVERFIRSTPOINT).toBool()) {
            painter->fillRect(getFirstPoint(), Qt::green);
        } else {
            painter->drawRect(getFirstPoint());
        }
    }

    // paint corner rectangles only if this item is selected
    if (this->isSelected()) {
        painter->setBrush(Qt::green);
        painter->drawRect(getTopLeftCorner());
        painter->drawRect(getBottomLeftCorner());
        painter->drawRect(getTopRightCorner());
        painter->drawRect(getBottomRightCorner());
    }
    if (!m_item->getRegisteredProperty(PolygonItem::P_DRAWINGMODE).toBool() && isSelected()) {
        pen.setWidth(5);
        painter->setPen(pen);
        for (int i = 0; i < points.length() - 1; ++i) {
            painter->drawPoint(
                QPointF(points[i]->getRegisteredProperty(PointItem::P_POSX).toReal(),
                        points[i]->getRegisteredProperty(PointItem::P_POSY).toReal()));
        }
        painter->setPen(QPen());
    }
}

QRectF PolygonView::boundingRect() const
{
    if (m_item->childItems().length() >= 1) {
        return calculateBoundingRectangle();
    } else {
        return QRectF(0, 0, m_width, m_heigth);
    }
}

// void PolygonView::setWidth(qreal width)
//{
//    m_width = width;
//}

// void PolygonView::setHeigth(qreal heigth)
//{
//    m_heigth = heigth;
//}

// void PolygonView::isDrawingMode(QPointF firstPoint)
//{
//    QPoint point(firstPoint.x(), firstPoint.y());
//    QList<ParameterizedItem*> points =  m_item->childItems();
//    m_item->setRegisteredProperty(PolygonItem::P_DRAWINGMODE, true);
//    m_polygon.append(point);
//    if (m_firstPoint.contains(point) && points.length() - 1 >= 2) {
//        points[points.length() - 1]->setRegisteredProperty(PointItem::P_POSX,
//        points[0]->getRegisteredProperty(PointItem::P_POSX).toReal());
//        points[points.length() - 1]->setRegisteredProperty(PointItem::P_POSY,
//        points[0]->getRegisteredProperty(PointItem::P_POSY).toReal());
//        m_item->setRegisteredProperty(PolygonItem::P_DRAWINGMODE, false);
//    }
//    calculateBoundingRectangle();
//}

// bool PolygonView::getDrawingMode() const
//{
//    return m_item->getRegisteredProperty(PolygonItem::P_DRAWINGMODE).toBool();
//}

bool PolygonView::checkCornerClicked(QGraphicsSceneMouseEvent *event)
{
    QList<ParameterizedItem *> points = m_item->childItems();
    for (int i = 0; i < points.length() - 1; ++i) {
        QGraphicsRectItem rectangle(
            points[i]->getRegisteredProperty(PointItem::P_POSX).toReal() - 2.5,
            points[i]->getRegisteredProperty(PointItem::P_POSY).toReal() - 2.5, 5, 5);
        if (rectangle.contains(event->pos())) {
            if (i != points.length() - 1 && i != 0) {
                m_currentPoint1 = i;
            } else {
                m_currentPoint1 = 0;
                m_currentPoint2 = points.length() - 1;
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
    //    setX(smallestXValue - 20);
    //    setY(smallestYValue - 20);
    //    m_width = biggestXValue + 20 - x();
    //    m_heigth = biggestYValue + 20 - y();

    return QRectF(QPointF(smallestXValue - 20, smallestYValue - 20),
                  QPointF(biggestXValue + 20, biggestYValue + 20));
}

void PolygonView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (checkCornerClicked(event)) {
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
            //        calculateBoundingRectangle();
            setCursor(Qt::CrossCursor);
            if (m_currentPoint1 == 0 || m_currentPoint1 == m_polygon.length() - 1) {
                points[m_currentPoint1]->setRegisteredProperty(PointItem::P_POSX, event->pos().x());
                points[m_currentPoint1]->setRegisteredProperty(PointItem::P_POSY, event->pos().y());
                points[m_currentPoint2]->setRegisteredProperty(PointItem::P_POSX, event->pos().x());
                points[m_currentPoint2]->setRegisteredProperty(PointItem::P_POSY, event->pos().y());
            } else {
                points[m_currentPoint1]->setRegisteredProperty(PointItem::P_POSX, event->pos().x());
                points[m_currentPoint1]->setRegisteredProperty(PointItem::P_POSY, event->pos().y());
            }
            update();
            //        calculateBoundingRectangle();

        } else if (!m_item->getRegisteredProperty(PolygonItem::P_DRAWINGMODE).toBool()) {
            this->setFlag(QGraphicsItem::ItemIsMovable, true);
            QGraphicsItem::mouseMoveEvent(event);
        }
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
}

void PolygonView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    m_changeCornerMode = false;
    setCursor(Qt::ArrowCursor);
    QGraphicsItem::mouseReleaseEvent(event);
}

void PolygonView::setInclude()
{
    m_item->setRegisteredProperty(PolygonItem::P_COLOR, 0);
}

QRectF PolygonView::getTopLeftCorner()
{
    return QRectF(boundingRect().x(), boundingRect().y(), 10, 10);
}

QRectF PolygonView::getTopRightCorner()
{
    return QRectF(boundingRect().x() + boundingRect().width() - 10, boundingRect().y() + 10, 10,
                  10);
}

QRectF PolygonView::getBottomLeftCorner()
{
    return QRectF(boundingRect().x(), boundingRect().y() + boundingRect().height() - 10, 10, 10);
}

QRectF PolygonView::getBottomRightCorner()
{
    return QRectF(boundingRect().x() + boundingRect().width() - 10,
                  boundingRect().y() + boundingRect().height() - 10, 10, 10);
}

QRectF PolygonView::getFirstPoint() const
{
    return QRectF(m_item->getRegisteredProperty(PolygonItem::P_FIRSTPOINTXVALUE).toReal() - 2.5,
                  m_item->getRegisteredProperty(PolygonItem::P_FIRSTPOINTYVALUE).toReal() - 2.5, 5,
                  5);
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

void PolygonView::onPropertyChange(const QString &propertyName)
{
    qDebug() << "void PolygonView::onPropertyChange(const QString &propertyName)";
}

void PolygonView::onSubItemPropertyChanged(QString, QString)
{
    qDebug() << "void PolygonView::onSubItemPropertyChanged(QString,QString)";
}
