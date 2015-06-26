
#include "PolygonView.h"
#include "ParameterizedItem.h"
#include "PolygonItem.h"
#include "PointItem.h"
#include <iostream>
#include <cmath>

PolygonView::PolygonView()
    : m_firstPoint(QRectF()), m_changeCornerMode(false), m_corner(NONE),
      m_currentPoint1(0), m_currentPoint2(0)

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
    QPainterPath lines;
    lines.moveTo(points[0]->getRegisteredProperty(PointItem::P_POSX).toReal(),
                 points[0]->getRegisteredProperty(PointItem::P_POSY).toReal());
    for (int i = 1; i < points.length() - 1; ++i) {
        lines.lineTo(points[i]->getRegisteredProperty(PointItem::P_POSX).toReal(),
                     points[i]->getRegisteredProperty(PointItem::P_POSY).toReal());
    }
    painter->drawPath(lines);

//        painter->drawPolyline(m_polygon);

    if (points[0]->getRegisteredProperty(PointItem::P_POSX).toReal()
            == points[points.length() - 1]->getRegisteredProperty(PointItem::P_POSX).toReal()
        && points[0]->getRegisteredProperty(PointItem::P_POSY).toReal()
               == points[points.length() - 1]->getRegisteredProperty(PointItem::P_POSY).toReal()) {

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

    if (points.length() >= 1 && m_item->getRegisteredProperty(PolygonItem::P_DRAWINGMODE).toBool()) {
        pen.setWidth(1);
        m_firstPoint.setRect(points[0]->getRegisteredProperty(PointItem::P_POSX).toReal() - 2.5,
                             points[0]->getRegisteredProperty(PointItem::P_POSY).toReal() - 2.5, 5,
                             5);
        if (m_item->getRegisteredProperty(PolygonItem::P_MOUSEISOVERFIRSTPOINT).toBool()) {
            painter->fillRect(m_firstPoint, Qt::green);
        } else {
            painter->drawRect(m_firstPoint);
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
    if (m_item->getRegisteredProperty(PolygonItem::P_DRAWINGMODE).toBool() == false && isSelected()) {
        pen.setWidth(5);
        painter->setPen(pen);
        for(int i = 0; i < points.length() - 1; ++i) {
            painter->drawPoint(QPointF(points[i]->getRegisteredProperty(PointItem::P_POSX).toReal(),points[i]->getRegisteredProperty(PointItem::P_POSY).toReal()));
        }
        painter->setPen(QPen());
    }
}

QRectF PolygonView::boundingRect() const
{
    return QRectF(0 - 10, 0 - 10, m_width + 20, m_heigth + 20);
}

//void PolygonView::setWidth(qreal width)
//{
//    m_width = width;
//}

//void PolygonView::setHeigth(qreal heigth)
//{
//    m_heigth = heigth;
//}

//void PolygonView::isDrawingMode(QPointF firstPoint)
//{
//    QPoint point(firstPoint.x(), firstPoint.y());
//    QList<ParameterizedItem*> points =  m_item->childItems();
//    m_item->setRegisteredProperty(PolygonItem::P_DRAWINGMODE, true);
//    m_polygon.append(point);
//    if (m_firstPoint.contains(point) && points.length() - 1 >= 2) {
//        points[points.length() - 1]->setRegisteredProperty(PointItem::P_POSX, points[0]->getRegisteredProperty(PointItem::P_POSX).toReal());
//        points[points.length() - 1]->setRegisteredProperty(PointItem::P_POSY, points[0]->getRegisteredProperty(PointItem::P_POSY).toReal());
//        m_item->setRegisteredProperty(PolygonItem::P_DRAWINGMODE, false);
//    }
//    calculateBoundingRectangle();
//}

//bool PolygonView::getDrawingMode() const
//{
//    return m_item->getRegisteredProperty(PolygonItem::P_DRAWINGMODE).toBool();
//}

void PolygonView::setMouseIsOverFirstPoint(bool mouseIsOverFirstPoint)
{
    m_mouseIsOverFirstPoint = mouseIsOverFirstPoint;
}

QRectF PolygonView::getFirstPoint() const
{
    return m_firstPoint;
}

bool PolygonView::checkCornerClicked(QGraphicsSceneMouseEvent *event)
{
    QList<ParameterizedItem*> points = m_item->childItems();
    for (int i = 0; i < points.length() - 1; ++i) {
        QGraphicsRectItem rectangle(points[0]->getRegisteredProperty(PointItem::P_POSX).toReal() - 2.5, points[0]->getRegisteredProperty(PointItem::P_POSY).toReal() - 2.5, 5, 5);
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

void PolygonView::calculateBoundingRectangle()
{
    QList<ParameterizedItem*> points = m_item->childItems();
    int smallestXValue = points[0]->getRegisteredProperty(PointItem::P_POSX).toReal();
    int biggestXValue = points[0]->getRegisteredProperty(PointItem::P_POSX).toReal();
    int smallestYValue = points[0]->getRegisteredProperty(PointItem::P_POSY).toReal();
    int biggestYValue = points[0]->getRegisteredProperty(PointItem::P_POSY).toReal();

    for (int i = 0; i < points.length() - 1; ++i) {
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
    setX(smallestXValue - 20);
    setY(smallestYValue - 20);
    m_width = biggestXValue + 20 - x();
    m_heigth = biggestYValue + 20 - y();
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
        calculateBoundingRectangle();
        setCursor(Qt::CrossCursor);
        if (m_currentPoint1 == 0 || m_currentPoint1 == m_polygon.length() - 1) {
            m_polygon[m_currentPoint1] = QPoint(event->pos().x(), event->scenePos().y());
            m_polygon[m_currentPoint2] = QPoint(event->pos().x(), event->scenePos().y());
        } else {
            m_polygon[m_currentPoint1] = QPoint(event->pos().x(), event->scenePos().y());
        }
        calculateBoundingRectangle();

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
    return QRectF(0 - 5, 0 - 5, 10, 10);
}

QRectF PolygonView::getTopRightCorner()
{
    return QRectF(0 + boundingRect().width() - 5, 0 - 5, 10, 10);
}

QRectF PolygonView::getBottomLeftCorner()
{
    return QRectF(0 - 5, 0 + boundingRect().height() - 5, 10, 10);
}

QRectF PolygonView::getBottomRightCorner()
{
    return QRectF(0 + boundingRect().width() - 5, 0 + boundingRect().height() - 5, 10, 10);
}

ParameterizedItem *PolygonView::getParameterizedItem()
{
    return m_item;
}

void PolygonView::setParameterizedItem(ParameterizedItem *item)
{
    m_item = item;
    connect(m_item, SIGNAL(propertyChanged(const QString &)), this,
            SLOT(onPropertyChange(const QString &)));
    connect(m_item, SIGNAL(subItemPropertyChanged(QString,QString)), this, SLOT(onSubItemPropertyChanged(QString,QString)));
    connect(m_item, SIGNAL(subItemChanged(QString)), this, SLOT(onSubItemChanged(QString)));
}

void PolygonView::setExclude()
{
    m_item->setRegisteredProperty(PolygonItem::P_COLOR, 1);
}


void PolygonView::onPropertyChange(const QString &propertyName)
{

}

void PolygonView::onSubItemPropertyChanged(QString,QString)
{

}

void PolygonView::onSubItemChanged(QString)
{
    QList<ParameterizedItem*> points =  m_item->childItems();
    QPointF point(points[points.length() - 1]->getRegisteredProperty(PointItem::P_POSX).toReal(),points[points.length() - 1]->getRegisteredProperty(PointItem::P_POSY).toReal());
    m_item->setRegisteredProperty(PolygonItem::P_DRAWINGMODE, true);
    if (m_firstPoint.contains(point) && points.length() - 1 >= 2) {
        points[points.length() - 1]->setRegisteredProperty(PointItem::P_POSX, points[0]->getRegisteredProperty(PointItem::P_POSX).toReal());
        points[points.length() - 1]->setRegisteredProperty(PointItem::P_POSY, points[0]->getRegisteredProperty(PointItem::P_POSY).toReal());
        m_item->setRegisteredProperty(PolygonItem::P_DRAWINGMODE, false);
    }
    calculateBoundingRectangle();
    update();
}
