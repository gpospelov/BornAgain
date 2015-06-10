
#include "Polygon.h"
#include <iostream>

Polygon::Polygon(qreal posX, qreal posY, qreal width, qreal heigth)
    : m_posX(posX), m_posY(posY), m_width(width), m_heigth(heigth),
      m_topLeftCorner(new QGraphicsRectItem(m_posX - 5, m_posY - 5, 10, 10)),
      m_bottomLeftCorner(new QGraphicsRectItem(m_posX + m_width - 5, m_posY - 5, 10, 10)),
      m_topRightCorner(new QGraphicsRectItem(m_posX + m_width - 5, m_posY - 5, 10, 10)),
      m_bottomRightCorner(
          new QGraphicsRectItem(m_posX + m_width - 5, m_posY + m_heigth - 5, 10, 10)),
      m_firstPoint(new QGraphicsRectItem),m_resizeMode(false), m_rotationMode(false),
      m_drawingMode(false), m_changeCornerMode(false), m_corner(NONE), m_currentPoint1(0),
      m_currentPoint2(0)

{
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->cursor().setShape(Qt::ClosedHandCursor);
    this->setAcceptHoverEvents(true);
}

void Polygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    delete m_topLeftCorner;
    delete m_topRightCorner;
    delete m_bottomLeftCorner;
    delete m_bottomRightCorner;
    prepareGeometryChange();
    painter->setRenderHints(QPainter::Antialiasing);
    painter->drawPolyline(m_polygon);
//    painter->drawLines(m_polygon);
    QPen pen;
    pen.setWidth(5);
    if(m_polygon.length() >= 1 && m_drawingMode) {
      delete m_firstPoint;
      painter->drawRect(m_polygon[0].x()  - 2.5  ,m_polygon[0].y()  - 2.5 , 5, 5);
    }

    if (this->isSelected()) {
        painter->setBrush(Qt::green);
        painter->drawRect(m_posX - 5, m_posY - 5, 10, 10);
        painter->drawRect(m_posX + m_width - 5, m_posY - 5, 10, 10);
        painter->drawRect(m_posX - 5, m_posY + m_heigth - 5, 10, 10);
        painter->drawRect(m_posX + m_width - 5, m_posY + m_heigth - 5, 10, 10);
    }
    if(m_drawingMode == false && isSelected()) {
        painter->setPen(pen);
        painter->drawPoints(m_polygon);
        painter->setPen(QPen());
    }

    m_topLeftCorner = new QGraphicsRectItem(m_posX - 5, m_posY - 5, 10, 10);
    m_bottomLeftCorner = new QGraphicsRectItem(m_posX - 5, m_posY + m_heigth - 5, 10, 10);
    m_topRightCorner = new QGraphicsRectItem(m_posX + m_width - 5, m_posY - 5, 10, 10);
    m_bottomRightCorner
        = new QGraphicsRectItem(m_posX + m_width - 5, m_posY + m_heigth - 5, 10, 10);
    if(m_polygon.length() >= 1) {
         m_firstPoint = new QGraphicsRectItem(m_polygon[0].x() - 2.5,m_polygon[0].y() - 2.5, 5, 5);
    }

}

QRectF Polygon::boundingRect() const
{
    return QRectF(m_posX - 10, m_posY - 10, m_width + 50, m_heigth + 50);
}

void Polygon::checkResizeRules(QGraphicsSceneMouseEvent *event)
{
    if (m_corner == TOPLEFT) {
        if (m_topRightCorner->pos().x() <= event->pos().x()) {
            m_corner = TOPRIGHT;
            setCursor(Qt::SizeBDiagCursor);

        } else if (m_bottomLeftCorner->pos().y() <= event->pos().y()) {
            m_corner = BOTTOMLEFT;
            setCursor(Qt::SizeBDiagCursor);
        }
    } else if (m_corner == TOPRIGHT) {
        if (event->pos().x() <= m_topLeftCorner->pos().x()) {
            m_corner = TOPLEFT;
            setCursor(Qt::SizeFDiagCursor);

        } else if (m_bottomRightCorner->pos().y() <= event->pos().y()) {
            m_corner = BOTTOMRIGHT;
            setCursor(Qt::SizeFDiagCursor);
        }
    } else if (m_corner == BOTTOMLEFT) {
        if (m_bottomRightCorner->pos().x() <= event->pos().x()) {
            m_corner = BOTTOMRIGHT;
            setCursor(Qt::SizeFDiagCursor);

        } else if (event->pos().y() <= m_topLeftCorner->pos().y()) {
            m_corner = TOPLEFT;
            setCursor(Qt::SizeFDiagCursor);
        }
    } else if (m_corner == BOTTOMRIGHT) {
        if (event->pos().x() <= m_bottomRightCorner->pos().x()) {
            m_corner = BOTTOMLEFT;
            setCursor(Qt::SizeBDiagCursor);

        } else if (event->pos().y() <= m_bottomRightCorner->pos().y()) {
            m_corner = TOPRIGHT;
            setCursor(Qt::SizeBDiagCursor);
        }
    }
}

void Polygon::calculateResize(QGraphicsSceneMouseEvent *event)
{
    this->setFlag(QGraphicsItem::ItemIsMovable, false);
    checkResizeRules(event);

    if (m_corner == TOPLEFT) {
        m_width = m_topRightCorner->pos().x() - event->pos().x();
        m_heigth = m_bottomLeftCorner->pos().y() - event->pos().y();
        m_posX = event->pos().x();
        m_posY = event->pos().y();

    } else if (m_corner == BOTTOMLEFT) {
        m_width = m_bottomRightCorner->pos().x() - event->pos().x();
        m_heigth = event->pos().y() - m_topLeftCorner->pos().y();
        m_posX = event->pos().x();
        m_posY = event->pos().y() - m_heigth;

    } else if (m_corner == TOPRIGHT) {
        m_width = event->pos().x() - m_topLeftCorner->pos().x();
        m_heigth = m_bottomRightCorner->pos().y() - event->pos().y();
        m_posX = event->pos().x() - m_width;
        m_posY = event->pos().y();
    }

    else if (m_corner == BOTTOMRIGHT) {
        m_width = event->pos().x() - m_bottomLeftCorner->pos().x();
        m_heigth = event->pos().y() - m_topRightCorner->pos().y();
        m_posX = event->pos().x() - m_width;
        m_posY = event->pos().y() - m_heigth;
    }
}

qreal Polygon::calculateRotation(QGraphicsSceneMouseEvent *event)
{
    qreal lengthOfHypotenuse = sqrt(pow(m_width / 2, 2) + pow(m_heigth / 2, 2));
    qreal offsetAngle = acos((m_width / 2) / lengthOfHypotenuse) * 180 / M_PI;
    qreal radians = atan(
        (event->scenePos().y() - this->mapToScene(m_posX + m_width / 2, m_posY + m_heigth / 2).y())
        / (event->scenePos().x()
           - this->mapToScene(m_posX + m_width / 2, m_posY + m_heigth / 2).x()));

    if (m_corner == TOPLEFT) {
        return radians * 180 / M_PI - offsetAngle;

    } else if (m_corner == TOPRIGHT) {
        return radians * 180 / M_PI + offsetAngle - 180;

    } else if (m_corner == BOTTOMLEFT) {
        return radians * 180 / M_PI + offsetAngle - 180;

    } else if (m_corner == BOTTOMRIGHT) {
        return radians * 180 / M_PI - offsetAngle;
    }
    return 0;
}


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
        else if(m_polygon[i].x() > biggestXValue) {
            biggestXValue = m_polygon[i].x();
        }
        else if(m_polygon[i].y() < smallestYValue) {
            smallestYValue = m_polygon[i].y();
        }
        else if(m_polygon[i].y() > biggestYValue) {
            biggestYValue = m_polygon[i].y();
        }
    }
        m_posX = smallestXValue*0.9;
        m_posY = smallestYValue*0.9;
        m_width = biggestXValue *1.1 - m_posX;
        m_heigth = biggestYValue*1.1 - m_posY;
}

void Polygon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_topLeftCorner->contains(event->pos())) {
        m_resizeMode = true;
        m_corner = TOPLEFT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::SizeFDiagCursor);
    } else if (event->button() == Qt::LeftButton && m_bottomLeftCorner->contains(event->pos())) {
        m_resizeMode = true;
        m_corner = BOTTOMLEFT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::SizeBDiagCursor);
    } else if (event->button() == Qt::LeftButton && m_topRightCorner->contains(event->pos())) {
        m_resizeMode = true;
        m_corner = TOPRIGHT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::SizeBDiagCursor);
    }
    else if (event->button() == Qt::LeftButton && m_bottomRightCorner->contains(event->pos())) {
        m_resizeMode = true;
        m_corner = BOTTOMRIGHT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::SizeFDiagCursor);
    } else if (m_drawingMode) {
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        m_polygon.append(QPoint(event->pos().x(), event->pos().y()));
        if(m_firstPoint->contains(event->pos()) && m_polygon.length() >= 2) {
            m_polygon.remove(m_polygon.length()-1);
            m_polygon[m_polygon.length()-1] = QPoint(m_polygon[0].x(), m_polygon[0].y());
            m_drawingMode = false;
        }
        std::cout << m_polygon.length() <<std::endl;
    }
    else if (checkCornerClicked(event)) {
        m_changeCornerMode = true;
    }
    else if(event->button() == Qt::RightButton) {
        m_drawingMode = false;
    } else {
        m_resizeMode = false;
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mousePressEvent(event);
    }
}

void Polygon::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    if (m_corner != NONE && m_resizeMode) {
        calculateResize(event);
    } else if (m_corner != NONE && m_rotationMode) {
        QTransform transform;
        transform.translate(m_posX + m_width * 0.5, m_posY + m_heigth * 0.5);
        transform.rotate(calculateRotation(event));
        transform.translate(-(m_posX + m_width * 0.5), -(m_posY + m_heigth * 0.5));
        setTransform(transform);       
    }
    else if (m_changeCornerMode) {
        if(m_currentPoint1 == 0 || m_currentPoint1 == m_polygon.length()-1) {
            m_polygon[m_currentPoint1] = QPoint(event->pos().x(), event->pos().y());
            m_polygon[m_currentPoint2] = QPoint(event->pos().x(), event->pos().y());
        }
        else {
            m_polygon[m_currentPoint1] = QPoint(event->pos().x(), event->pos().y());
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
    m_resizeMode = false;
    m_rotationMode = false;
    m_changeCornerMode = false;
    setCursor(Qt::ArrowCursor);
    QGraphicsItem::mouseReleaseEvent(event);
}

void Polygon::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_topLeftCorner->contains(event->pos())) {
        m_resizeMode = false;
        m_rotationMode = true;
        m_corner = TOPLEFT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::SizeFDiagCursor);

    } else if (event->button() == Qt::LeftButton && m_bottomLeftCorner->contains(event->pos())) {
        m_resizeMode = false;
        m_rotationMode = true;
        m_corner = BOTTOMLEFT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::SizeBDiagCursor);
    } else if (event->button() == Qt::LeftButton && m_topRightCorner->contains(event->pos())) {
        m_resizeMode = false;
        m_rotationMode = true;
        m_corner = TOPRIGHT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::SizeBDiagCursor);
    }
    else if (event->button() == Qt::LeftButton && m_bottomRightCorner->contains(event->pos())) {
        m_resizeMode = false;
        m_rotationMode = true;
        m_corner = BOTTOMRIGHT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::SizeFDiagCursor);
    } else if (event->button() == Qt::LeftButton && !m_drawingMode) {
        m_resizeMode = false;
        m_rotationMode = false;
        m_drawingMode = true;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
    } else if (m_drawingMode) {
        m_drawingMode = false;
    } else {
        m_resizeMode = false;
        m_rotationMode = false;
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mouseDoubleClickEvent(event);
    }
}

void Polygon::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event);
}

void Polygon::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
        if(m_drawingMode) {
            setCursor(Qt::CrossCursor);
            if(m_polygon.length() >= 2) {
                 m_polygon[m_polygon.length() -1] = QPoint(event->pos().x(), event->pos().y());
            }
        }

    QGraphicsItem::hoverMoveEvent(event);
}

void Polygon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event);
}
