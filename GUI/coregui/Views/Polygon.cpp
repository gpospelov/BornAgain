
#include "Polygon.h"
#include <iostream>

Polygon::Polygon(qreal posX, qreal posY, qreal width, qreal heigth)
    : m_posX(posX), m_posY(posY), m_width(width), m_heigth(heigth),
      m_topLeftCorner(new QGraphicsRectItem(m_posX - 5, m_posY - 5, 10, 10)),
      m_bottomLeftCorner(new QGraphicsRectItem(m_posX + m_width - 5, m_posY - 5, 10, 10)),
      m_topRightCorner(new QGraphicsRectItem(m_posX + m_width - 5, m_posY - 5, 10, 10)),
      m_bottomRightCorner(
          new QGraphicsRectItem(m_posX + m_width - 5, m_posY + m_heigth - 5, 10, 10)),
      m_resizeMode(false), m_rotationMode(false), m_drawingMode(false), m_numberOfPoints(1),
      m_corner(NONE)

{
    m_points.append(QPoint(0, 0));
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

    painter->setRenderHints(QPainter::Antialiasing);
    this->prepareGeometryChange();
    QPolygon polygon;
    for (int i = 0; i < m_numberOfPoints - 1; ++i) {
        polygon << m_points[i];
    }
    painter->drawPolygon(polygon);

    if (this->isSelected()) {
        painter->setBrush(Qt::green);
        this->prepareGeometryChange();
        painter->drawRect(m_posX - 5, m_posY - 5, 10, 10);
        this->prepareGeometryChange();
        painter->drawRect(m_posX + m_width - 5, m_posY - 5, 10, 10);
        this->prepareGeometryChange();
        painter->drawRect(m_posX - 5, m_posY + m_heigth - 5, 10, 10);
        this->prepareGeometryChange();
        painter->drawRect(m_posX + m_width - 5, m_posY + m_heigth - 5, 10, 10);
    }

    m_topLeftCorner = new QGraphicsRectItem(m_posX - 5, m_posY - 5, 10, 10);
    m_bottomLeftCorner = new QGraphicsRectItem(m_posX - 5, m_posY + m_heigth - 5, 10, 10);
    m_topRightCorner = new QGraphicsRectItem(m_posX + m_width - 5, m_posY - 5, 10, 10);
    m_bottomRightCorner
        = new QGraphicsRectItem(m_posX + m_width - 5, m_posY + m_heigth - 5, 10, 10);
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
        m_points.append(QPoint(event->pos().x(), event->pos().y()));
        m_numberOfPoints = m_points.length();
        m_isDeleted = false;
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
    } else if (m_drawingMode) {
        m_points.insert(m_numberOfPoints - 1, QPoint(event->pos().x(), event->pos().y()));
    } else if (!m_drawingMode) {
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
    setCursor(Qt::ArrowCursor);
    //    if(m_drawingMode) {
    //        m_points.append(QPoint(event->pos().x(), event->pos().y()));
    //    }
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
    //    if(m_drawingMode) {
    //        m_points.append(QPoint(event->pos().x(), event->pos().y()));
    //        event->accept();
    //    }
    //    else {
    std::cout << "mouse hover enter event" << std::endl;
    QGraphicsItem::hoverEnterEvent(event);
    //    }
}

void Polygon::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    //    lastMousePosition = QPoint(event->pos().x(), event->pos().y());
    //    QTimer *timer = new QTimer;
    //    timer->setSingleShot(true);
    ////    timer.setInterval(2000);
    //    timer->start(2000);

    //    if(m_drawingMode) {
    //        if(lastMousePosition.x() == event->pos().x() && lastMousePosition.y() ==
    //        event->pos().y() && !timer->isActive()) {
    //            m_points.append(QPoint(event->pos().x(), event->pos().y()));
    //            m_isDeleted = true;
    //            std::cout << "yes" << std::endl;
    //        }
    //        if(m_numberOfPoints > 1 && timer->isActive() && m_isDeleted){
    //            std::cout << "deleting" << std::endl;
    //            m_points.remove(m_numberOfPoints-1);
    //            m_isDeleted = true;
    //        }
    //    }
    //    if(!timer->isActive()) {
    //        std::cout << "timer is out" << std::endl;
    //    }
    //    else {
    //        std::cout << "timer is running" << std::endl;
    //    }

    //    else {
    QGraphicsItem::hoverMoveEvent(event);
    //    }
}

void Polygon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    //    if(m_drawingMode && !m_isDeleted && m_numberOfPoints >1) {
    //       this->setFlag(QGraphicsItem::ItemIsMovable, false);
    //       m_points.remove(m_numberOfPoints-1);
    //       m_isDeleted = true;
    //    }
    //    event->accept();
    QGraphicsItem::hoverLeaveEvent(event);
}
