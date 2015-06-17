#include "Rectangle.h"
#include <iostream>
#include <cmath>

Rectangle::Rectangle(qreal posX, qreal posY, qreal width, qreal heigth)
    : m_posX(posX), m_posY(posY), m_width(width), m_heigth(heigth),
      m_topLeftCorner(QRectF (m_posX - 5, m_posY - 5, 10, 10)),
      m_bottomLeftCorner(QRectF (m_posX + m_width - 5, m_posY - 5, 10, 10)),
      m_topRightCorner(QRectF (m_posX + m_width - 5, m_posY - 5, 10, 10)),
      m_bottomRightCorner(
          QRectF (m_posX + m_width - 5, m_posY + m_heigth - 5, 10, 10)),
      m_resizeMode(false), m_rotationMode(false)
{
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(QGraphicsItem::ItemIsMovable);
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    // paint rectangle
    painter->setRenderHints(QPainter::Antialiasing);
    this->prepareGeometryChange();
    if(m_color == INCLUDE) {
        QBrush transRed(QColor(0xFF, 0, 0, 0x80));
        painter->fillRect(m_posX, m_posY, m_width, m_heigth,transRed);
    }
    else {
        QBrush transBlue(QColor(0, 0, 0xFF, 0x80));
        painter->fillRect(m_posX, m_posY, m_width, m_heigth,transBlue);
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
}

QRectF Rectangle::boundingRect() const
{
    return QRectF(m_posX - 10, m_posY - 10, m_width + 20, m_heigth + 20);
}

void Rectangle::checkResizeRules(QGraphicsSceneMouseEvent *event)
{
    if (m_corner == TOPLEFT) {
        if (m_posX + m_width <= event->pos().x()) {
            m_corner = TOPRIGHT;
            setCursor(Qt::SizeBDiagCursor);

        } else if (m_posY + m_heigth <= event->pos().y()) {
            m_corner = BOTTOMLEFT;
            setCursor(Qt::SizeBDiagCursor);
        }
    } else if (m_corner == TOPRIGHT) {
        if (event->pos().x() <= m_posX) {
            m_corner = TOPLEFT;
            setCursor(Qt::SizeFDiagCursor);

        } else if (m_posY + m_heigth <= event->pos().y()) {
            m_corner = BOTTOMRIGHT;
            setCursor(Qt::SizeFDiagCursor);
        }
    } else if (m_corner == BOTTOMLEFT) {
        if (m_posX + m_width <= event->pos().x()) {
            m_corner = BOTTOMRIGHT;
            setCursor(Qt::SizeFDiagCursor);

        } else if (event->pos().y() <= m_posY) {
            m_corner = TOPLEFT;
            setCursor(Qt::SizeFDiagCursor);
        }
    } else if (m_corner == BOTTOMRIGHT) {
        if (event->pos().x() <= m_posX) {
            m_corner = BOTTOMLEFT;
            setCursor(Qt::SizeBDiagCursor);

        } else if (event->pos().y() <= m_posY) {
            m_corner = TOPRIGHT;
            setCursor(Qt::SizeBDiagCursor);
        }
    }
}

void Rectangle::calculateResize(QGraphicsSceneMouseEvent *event)
{
    this->setFlag(QGraphicsItem::ItemIsMovable, false);
    checkResizeRules(event);

    if (m_corner == TOPLEFT) {
        m_width = m_posX + m_width - event->pos().x();
        m_heigth = m_posY + m_heigth - event->pos().y();
        m_posX = event->pos().x();
        m_posY = event->pos().y();

    } else if (m_corner == BOTTOMLEFT) {
        m_width = m_posX + m_width - event->pos().x();
        m_heigth = event->pos().y() - m_posY;
        m_posX = event->pos().x();

    } else if (m_corner == TOPRIGHT) {
        m_width = event->pos().x() - m_posX;
        m_heigth = m_posY + m_heigth - event->pos().y();
        m_posY = event->pos().y();
    }

    else if (m_corner == BOTTOMRIGHT) {
        m_width = event->pos().x() - m_posX;
        m_heigth = event->pos().y() - m_posY;
    }
}

qreal Rectangle::calculateRotation(QGraphicsSceneMouseEvent *event)
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

void Rectangle::setWidth(qreal width)
{
    m_width = width;
}

void Rectangle::setHeigth(qreal heigth)
{
    m_heigth = heigth;
}

void Rectangle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setFlag(QGraphicsItem::ItemIsMovable, false);

    //if one of the corners is clicked then go in to resize Mode
    if (event->button() == Qt::LeftButton && m_topLeftCorner.contains(event->pos())) {
        m_resizeMode = true;
        m_corner = TOPLEFT;
        setCursor(Qt::SizeFDiagCursor);

    } else if (event->button() == Qt::LeftButton && m_bottomLeftCorner.contains(event->pos())) {
        m_resizeMode = true;
        m_corner = BOTTOMLEFT;
        setCursor(Qt::SizeBDiagCursor);

    } else if (event->button() == Qt::LeftButton && m_topRightCorner.contains(event->pos())) {
        m_resizeMode = true;
        m_corner = TOPRIGHT;
        setCursor(Qt::SizeBDiagCursor);
    }

    else if (event->button() == Qt::LeftButton && m_bottomRightCorner.contains(event->pos())) {
        m_resizeMode = true;
        m_corner = BOTTOMRIGHT;
        setCursor(Qt::SizeFDiagCursor);

    // process as usual
    } else {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mousePressEvent(event);
    }
}

void Rectangle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //check which mode is active and process with the active mode
    if (m_corner != NONE && m_resizeMode) {
        calculateResize(event);

    } else if (m_corner != NONE && m_rotationMode) {
        QTransform transform;
        transform.translate(m_posX + m_width * 0.5, m_posY + m_heigth * 0.5);
        transform.rotate(calculateRotation(event));
        transform.translate(-(m_posX + m_width * 0.5), -(m_posY + m_heigth * 0.5));
        setTransform(transform);

    // process as usual
    } else {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void Rectangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // set all modes off, change cursor and process as usual
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    m_resizeMode = false;
    m_rotationMode = false;
    setCursor(Qt::ArrowCursor);
    QGraphicsItem::mouseReleaseEvent(event);
}

void Rectangle::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    //activate rotation mode
    if (event->button() == Qt::LeftButton && m_topLeftCorner.contains(event->pos())) {
        m_resizeMode = false;
        m_rotationMode = true;
        m_corner = TOPLEFT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::ClosedHandCursor);

    } else if (event->button() == Qt::LeftButton && m_bottomLeftCorner.contains(event->pos())) {
        m_resizeMode = false;
        m_rotationMode = true;
        m_corner = BOTTOMLEFT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::ClosedHandCursor);

    } else if (event->button() == Qt::LeftButton && m_topRightCorner.contains(event->pos())) {
        m_resizeMode = false;
        m_rotationMode = true;
        m_corner = TOPRIGHT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::ClosedHandCursor);
    }

    else if (event->button() == Qt::LeftButton && m_bottomRightCorner.contains(event->pos())) {
        m_resizeMode = false;
        m_rotationMode = true;
        m_corner = BOTTOMRIGHT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::ClosedHandCursor);

    } else {
        m_resizeMode = false;
        m_rotationMode = false;
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mouseDoubleClickEvent(event);
    }
}

void Rectangle::setInclude()
{
    m_color = INCLUDE;
    update();
}

void Rectangle::setExclude()
{
    m_color = EXCLUDE;
    update();
}

