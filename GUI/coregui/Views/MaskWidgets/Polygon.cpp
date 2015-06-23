
#include "Polygon.h"
#include <iostream>
#include <cmath>

Polygon::Polygon(qreal posX, qreal posY, qreal width, qreal heigth)
    : m_posX(posX), m_posY(posY), m_width(width), m_heigth(heigth),
      m_topLeftCorner(QRectF(m_posX - 5, m_posY - 5, 10, 10)),
      m_bottomLeftCorner(QRectF(m_posX + m_width - 5, m_posY - 5, 10, 10)),
      m_topRightCorner(QRectF(m_posX + m_width - 5, m_posY - 5, 10, 10)),
      m_bottomRightCorner(QRectF(m_posX + m_width - 5, m_posY + m_heigth - 5, 10, 10)),
      m_firstPoint(QRectF()),m_drawingMode(false), m_changeCornerMode(false), m_corner(NONE),
      m_currentPoint1(0), m_currentPoint2(0)

{
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    this->cursor().setShape(Qt::ClosedHandCursor);
    this->setAcceptHoverEvents(true);
}

void Polygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen;
    prepareGeometryChange();
    painter->setRenderHints(QPainter::Antialiasing);
    painter->drawPolyline(m_polygon);

    if(m_polygon[0].x() == m_polygon[m_polygon.length()-1].x() && m_polygon[0].y() == m_polygon[m_polygon.length()-1].y()) {
        if(m_color == INCLUDE) {
            QPainterPath path;
            QBrush transRed(QColor(0xFF, 0, 0, 0x80));
            path.moveTo(m_polygon[0].x(), m_polygon[0].y());
            for(int i = 1; i < m_polygon.length() - 1; ++i) {
                path.lineTo (m_polygon[i].x(), m_polygon[i].y());
            }
            painter->setPen (Qt :: NoPen);
            painter->fillPath (path, transRed);
        }
        else {
            QBrush transBlue(QColor(0, 0, 0xFF, 0x80));
            QPainterPath path;
            path.moveTo(m_polygon[0].x(), m_polygon[0].y());
            for(int i = 1; i < m_polygon.length() - 1; ++i) {
                path.lineTo (m_polygon[i].x(), m_polygon[i].y());
            }
            painter->setPen (Qt :: NoPen);
            painter->fillPath (path, transBlue);
        }
    }

    if(m_polygon.length() >= 1 && m_drawingMode) {
      pen.setWidth(1);
      m_firstPoint.setRect(m_polygon[0].x()  - 2.5  ,m_polygon[0].y()  - 2.5 , 5, 5);
      if(m_mouseIsOverFirstPoint) {
          painter->fillRect(m_firstPoint, Qt::green);
      }
      else {
          painter->drawRect(m_firstPoint);
      }
    }

    // paint corner rectangles only if this item is selected
    if (this->isSelected()) {

        // set values for corners
        m_topLeftCorner.setRect(m_posX - 5, m_posY - 5, 10, 10);
        m_bottomLeftCorner.setRect(m_posX - 5, m_posY + m_heigth - 5, 10, 10);
        m_topRightCorner.setRect(m_posX + m_width - 5, m_posY - 5, 10, 10);
        m_bottomRightCorner.setRect(m_posX + m_width - 5, m_posY + m_heigth - 5, 10, 10);

        painter->setBrush(Qt::green);
        painter->drawRect(m_topLeftCorner);
        painter->drawRect(m_topRightCorner);
        painter->drawRect(m_bottomLeftCorner);
        painter->drawRect(m_bottomRightCorner);
    }
    if(m_drawingMode == false && isSelected()) {
        pen.setWidth(5);
        painter->setPen(pen);
        painter->drawPoints(m_polygon);
        painter->setPen(QPen());
    }



}

QRectF Polygon::boundingRect() const
{
    return QRectF(m_posX - 10, m_posY - 10, m_width + 20, m_heigth + 20);
}

void Polygon::setWidth(qreal width)
{
    m_width = width;
}

void Polygon::setHeigth(qreal heigth)
{
    m_heigth = heigth;
}

void Polygon::setDrawingMode(QPointF firstPoint)
{
    QPoint point(firstPoint.x(), firstPoint.y());
    m_drawingMode = true;
    m_polygon.append(point);
    if(m_firstPoint.contains(point) && m_polygon.length() >= 2) {
        m_polygon[m_polygon.length()-1] = QPoint(m_polygon[0].x(), m_polygon[0].y());
        m_drawingMode = false;
    }
    calculateBoundingRectangle();
}

bool Polygon::getDrawingMode() const
{
    return m_drawingMode;
}

void Polygon::setMouseIsOverFirstPoint(bool mouseIsOverFirstPoint)
{
    m_mouseIsOverFirstPoint = mouseIsOverFirstPoint;
}

QRectF Polygon::getFirstPoint() const
{
    return m_firstPoint;
}

//void Polygon::checkResizeRules(QGraphicsSceneMouseEvent *event)
//{
//    {
//        if (m_corner == TOPLEFT) {
//            if (m_posX + m_width <= event->pos().x()) {
//                m_corner = TOPRIGHT;
//                setCursor(Qt::SizeBDiagCursor);

//            } else if (m_posY + m_heigth <= event->pos().y()) {
//                m_corner = BOTTOMLEFT;
//                setCursor(Qt::SizeBDiagCursor);
//            }
//        } else if (m_corner == TOPRIGHT) {
//            if (event->pos().x() <= m_posX) {
//                m_corner = TOPLEFT;
//                setCursor(Qt::SizeFDiagCursor);

//            } else if (m_posY + m_heigth <= event->pos().y()) {
//                m_corner = BOTTOMRIGHT;
//                setCursor(Qt::SizeFDiagCursor);
//            }
//        } else if (m_corner == BOTTOMLEFT) {
//            if (m_posX + m_width <= event->pos().x()) {
//                m_corner = BOTTOMRIGHT;
//                setCursor(Qt::SizeFDiagCursor);

//            } else if (event->pos().y() <= m_posY) {
//                m_corner = TOPLEFT;
//                setCursor(Qt::SizeFDiagCursor);
//            }
//        } else if (m_corner == BOTTOMRIGHT) {
//            if (event->pos().x() <= m_posX) {
//                m_corner = BOTTOMLEFT;
//                setCursor(Qt::SizeBDiagCursor);

//            } else if (event->pos().y() <= m_posY) {
//                m_corner = TOPRIGHT;
//                setCursor(Qt::SizeBDiagCursor);
//            }
//        }
//    }
//}

//void Polygon::calculateResize(QGraphicsSceneMouseEvent *event)
//{
//    this->setFlag(QGraphicsItem::ItemIsMovable, false);
//    checkResizeRules(event);

//    if (m_corner == TOPLEFT) {
//        m_width = m_posX + m_width - event->pos().x();
//        m_heigth = m_posY + m_heigth - event->pos().y();
//        m_posX = event->pos().x();
//        m_posY = event->pos().y();

//    } else if (m_corner == BOTTOMLEFT) {
//        m_width = m_posX + m_width - event->pos().x();
//        m_heigth = event->pos().y() - m_posY;
//        m_posX = event->pos().x();

//    } else if (m_corner == TOPRIGHT) {
//        m_width = event->pos().x() - m_posX;
//        m_heigth = m_posY + m_heigth - event->pos().y();
//        m_posY = event->pos().y();
//    }

//    else if (m_corner == BOTTOMRIGHT) {
//        m_width = event->pos().x() - m_posX;
//        m_heigth = event->pos().y() - m_posY;
//    }
//}

//qreal Polygon::calculateRotation(QGraphicsSceneMouseEvent *event)
//{
//    qreal lengthOfHypotenuse = sqrt(pow(m_width / 2, 2) + pow(m_heigth / 2, 2));
//    qreal offsetAngle = acos((m_width / 2) / lengthOfHypotenuse) * 180 / M_PI;
//    qreal radians = atan(
//        (event->scenePos().y() - this->mapToScene(m_posX + m_width / 2, m_posY + m_heigth / 2).y())
//        / (event->scenePos().x()
//           - this->mapToScene(m_posX + m_width / 2, m_posY + m_heigth / 2).x()));

//    if (m_corner == TOPLEFT) {
//        return radians * 180 / M_PI - offsetAngle;

//    } else if (m_corner == TOPRIGHT) {
//        return radians * 180 / M_PI + offsetAngle - 180;

//    } else if (m_corner == BOTTOMLEFT) {
//        return radians * 180 / M_PI + offsetAngle - 180;

//    } else if (m_corner == BOTTOMRIGHT) {
//        return radians * 180 / M_PI - offsetAngle;
//    }
//    return 0;
//}


bool Polygon::checkCornerClicked(QGraphicsSceneMouseEvent *event) {
    for(int i = 0; i < m_polygon.length()-1; ++i) {
        QGraphicsRectItem rectangle(m_polygon[i].x() -2.5, m_polygon[i].y() -2.5, 5, 5);
        if(rectangle.contains(event->pos())) {
            if(i != m_polygon.length()-1 && i != 0) {
                m_currentPoint1 = i;
            }
            else {
                m_currentPoint1 = 0;
                m_currentPoint2 = m_polygon.length() -1;
            }
            m_changeCornerMode = true;
            this->setFlag(QGraphicsItem::ItemIsMovable, false);
            return true;
        }
    }
    return false;
}

void Polygon::calculateBoundingRectangle()
{
    int smallestXValue = m_polygon[0].x();
    int biggestXValue = m_polygon[0].x();
    int smallestYValue = m_polygon[0].y();
    int biggestYValue = m_polygon[0].y();

    for(int i = 0; i < m_polygon.length()-1; ++i) {
        if(m_polygon[i].x() < smallestXValue) {
            smallestXValue = m_polygon[i].x();
        }
        if(m_polygon[i].x() > biggestXValue) {
            biggestXValue = m_polygon[i].x();
        }
        if(m_polygon[i].y() < smallestYValue) {
            smallestYValue = m_polygon[i].y();
        }
        if(m_polygon[i].y() > biggestYValue) {
            biggestYValue = m_polygon[i].y();
        }
    }
        m_posX = smallestXValue - 20;
        m_posY = smallestYValue - 20;
        m_width =  biggestXValue + 20 - m_posX;
        m_heigth = biggestYValue + 20 - m_posY;
}

void Polygon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    if (event->button() == Qt::LeftButton && m_topLeftCorner.contains(event->pos())) {
//        m_resizeMode = true;
//        m_corner = TOPLEFT;
//        this->setFlag(QGraphicsItem::ItemIsMovable, false);
//        setCursor(Qt::SizeFDiagCursor);
//    } else if (event->button() == Qt::LeftButton && m_bottomLeftCorner.contains(event->pos())) {
//        m_resizeMode = true;
//        m_corner = BOTTOMLEFT;
//        this->setFlag(QGraphicsItem::ItemIsMovable, false);
//        setCursor(Qt::SizeBDiagCursor);
//    } else if (event->button() == Qt::LeftButton && m_topRightCorner.contains(event->pos())) {
//        m_resizeMode = true;
//        m_corner = TOPRIGHT;
//        this->setFlag(QGraphicsItem::ItemIsMovable, false);
//        setCursor(Qt::SizeBDiagCursor);
//    }
//    else if (event->button() == Qt::LeftButton && m_bottomRightCorner.contains(event->pos())) {
//        m_resizeMode = true;
//        m_corner = BOTTOMRIGHT;
//        this->setFlag(QGraphicsItem::ItemIsMovable, false);
//        setCursor(Qt::SizeFDiagCursor);
//    }
//      if (m_drawingMode) {
//        this->setFlag(QGraphicsItem::ItemIsMovable, false);
//        m_polygon.append(QPoint(event->pos().x(), event->pos().y()));
//        if(m_firstPoint.contains(event->pos()) && m_polygon.length() >= 2) {
//            m_polygon.remove(m_polygon.length()-1);
//            m_polygon[m_polygon.length()-1] = QPoint(m_polygon[0].x(), m_polygon[0].y());
//            m_drawingMode = false;
//        }
//        calculateBoundingRectangle();
//    }
    if (checkCornerClicked(event)) {
        m_changeCornerMode = true;
    }
    else if(event->button() == Qt::RightButton) {
        m_drawingMode = false;
    } else {
//        m_resizeMode = false;
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mousePressEvent(event);
    }
}

void Polygon::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    if (m_corner != NONE && m_resizeMode) {
//        calculateResize(event);
//    } else if (m_corner != NONE && m_rotationMode) {
//        QTransform transform;
//        transform.translate(m_posX + m_width * 0.5, m_posY + m_heigth * 0.5);
//        transform.rotate(calculateRotation(event));
//        transform.translate(-(m_posX + m_width * 0.5), -(m_posY + m_heigth * 0.5));
//        setTransform(transform);
//    }
    if (m_changeCornerMode) {
        calculateBoundingRectangle();
        setCursor(Qt::CrossCursor);
        if(m_currentPoint1 == 0 || m_currentPoint1 == m_polygon.length()-1) {
            m_polygon[m_currentPoint1] = QPoint(event->pos().x(), event->scenePos().y());
            m_polygon[m_currentPoint2] = QPoint(event->pos().x(), event->scenePos().y());
        }
        else {
            m_polygon[m_currentPoint1] = QPoint(event->pos().x(), event->scenePos().y());
        }
        calculateBoundingRectangle();

    }
    else if (!m_drawingMode) {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mouseMoveEvent(event);
    }
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
}

void Polygon::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
//    m_resizeMode = false;
//    m_rotationMode = false;
    m_changeCornerMode = false;
    setCursor(Qt::ArrowCursor);
    QGraphicsItem::mouseReleaseEvent(event);
}

//void Polygon::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
//{
//    if (event->button() == Qt::LeftButton && m_topLeftCorner.contains(event->pos())) {
//        m_resizeMode = false;
//        m_rotationMode = true;
//        m_corner = TOPLEFT;
//        this->setFlag(QGraphicsItem::ItemIsMovable, false);
//        setCursor(Qt::SizeFDiagCursor);

//    } else if (event->button() == Qt::LeftButton && m_bottomLeftCorner.contains(event->pos())) {
//        m_resizeMode = false;
//        m_rotationMode = true;
//        m_corner = BOTTOMLEFT;
//        this->setFlag(QGraphicsItem::ItemIsMovable, false);
//        setCursor(Qt::SizeBDiagCursor);
//    } else if (event->button() == Qt::LeftButton && m_topRightCorner.contains(event->pos())) {
//        m_resizeMode = false;
//        m_rotationMode = true;
//        m_corner = TOPRIGHT;
//        this->setFlag(QGraphicsItem::ItemIsMovable, false);
//        setCursor(Qt::SizeBDiagCursor);
//    }
//    else if (event->button() == Qt::LeftButton && m_bottomRightCorner.contains(event->pos())) {
//        m_resizeMode = false;
//        m_rotationMode = true;
//        m_corner = BOTTOMRIGHT;
//        this->setFlag(QGraphicsItem::ItemIsMovable, false);
//        setCursor(Qt::SizeFDiagCursor);
//    } else if (event->button() == Qt::LeftButton && !m_drawingMode) {
//        m_resizeMode = false;
//        m_rotationMode = false;
//        m_drawingMode = true;
//        this->setFlag(QGraphicsItem::ItemIsMovable, false);
//    } else if (m_drawingMode) {
//        m_drawingMode = false;
//    } else {
//        m_resizeMode = false;
//        m_rotationMode = false;
//        this->setFlag(QGraphicsItem::ItemIsMovable, true);
//        QGraphicsItem::mouseDoubleClickEvent(event);
//    }
//}

//void Polygon::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
//{
//    QGraphicsItem::hoverEnterEvent(event);
//}

//void Polygon::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
//{
//        if(m_drawingMode && m_firstPoint.contains(event->pos())) {
//            m_mouseIsOverFirstPoint = true;
//        }
//        else {
//            m_mouseIsOverFirstPoint = false;
//        }

//    QGraphicsItem::hoverMoveEvent(event);
//}

//void Polygon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
//{
//    QGraphicsItem::hoverLeaveEvent(event);
//}

void Polygon::setInclude()
{
    m_color = INCLUDE;
}

void Polygon::setExclude()
{
    m_color = EXCLUDE;
}
