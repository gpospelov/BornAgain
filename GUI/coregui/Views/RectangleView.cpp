
#include "RectangleView.h"
#include "RectangleItem.h"
#include <iostream>
#include <cmath>

RectangleView::RectangleView(qreal posX, qreal posY, qreal width, qreal heigth)
{
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(QGraphicsItem::ItemIsMovable);
}

void RectangleView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    // paint rectangle
    painter->setRenderHints(QPainter::Antialiasing);
    this->prepareGeometryChange();
    if(m_color == INCLUDE) {
        QBrush transRed(QColor(0xFF, 0, 0, 0x80));
        painter->fillRect(m_item->getXPos(), m_item->getYPos(), m_item->getWidth(), m_item->getHeight(),transRed);
    }
    else {
        QBrush transBlue(QColor(0, 0, 0xFF, 0x80));
        painter->fillRect(m_item->getXPos(), m_item->getYPos(), m_item->getWidth(), m_item->getHeight(),transBlue);
    }

    // paint corner rectangles only if this item is selected
    if (this->isSelected()) {

        painter->setBrush(Qt::green);
        painter->drawRect(getTopLeftCorner());
        painter->drawRect(getBottomLeftCorner());
        painter->drawRect(getTopRightCorner());
        painter->drawRect(getBottomRightCorner());
    }
}

QRectF RectangleView::boundingRect() const
{
    return QRectF(m_item->getXPos() - 10, m_item->getYPos() - 10, m_item->getWidth() + 20,  m_item->getHeight() + 20);
}

void RectangleView::checkResizeRules(QGraphicsSceneMouseEvent *event)
{
    if (m_corner == TOPLEFT) {
        if (m_item->getXPos() + m_item->getWidth() <= event->pos().x()) {
            m_corner = TOPRIGHT;
            setCursor(Qt::SizeBDiagCursor);

        } else if (m_item->getYPos() + m_item->getHeight() <= event->pos().y()) {
            m_corner = BOTTOMLEFT;
            setCursor(Qt::SizeBDiagCursor);
        }
    } else if (m_corner == TOPRIGHT) {
        if (event->pos().x() <= m_item->getXPos()) {
            m_corner = TOPLEFT;
            setCursor(Qt::SizeFDiagCursor);

        } else if (m_item->getYPos() + m_item->getHeight() <= event->pos().y()) {
            m_corner = BOTTOMRIGHT;
            setCursor(Qt::SizeFDiagCursor);
        }
    } else if (m_corner == BOTTOMLEFT) {
        if (m_item->getXPos() + m_item->getWidth() <= event->pos().x()) {
            m_corner = BOTTOMRIGHT;
            setCursor(Qt::SizeFDiagCursor);

        } else if (event->pos().y() <= m_item->getYPos()) {
            m_corner = TOPLEFT;
            setCursor(Qt::SizeFDiagCursor);
        }
    } else if (m_corner == BOTTOMRIGHT) {
        if (event->pos().x() <= m_item->getXPos()) {
            m_corner = BOTTOMLEFT;
            setCursor(Qt::SizeBDiagCursor);

        } else if (event->pos().y() <= m_item->getYPos()) {
            m_corner = TOPRIGHT;
            setCursor(Qt::SizeBDiagCursor);
        }
    }
}

void RectangleView::calculateResize(QGraphicsSceneMouseEvent *event)
{
    this->setFlag(QGraphicsItem::ItemIsMovable, false);
    checkResizeRules(event);

    if (m_corner == TOPLEFT) {
        m_item->getWidth() = m_item->getXPos() + m_item->getWidth() - event->pos().x();
        m_item->getHeight() = m_item->getYPos() + m_item->getHeight() - event->pos().y();
        m_item->getXPos() = event->pos().x();
        m_item->getYPos() = event->pos().y();

    } else if (m_corner == BOTTOMLEFT) {
        m_item->getWidth() = m_item->getXPos() + m_item->getWidth() - event->pos().x();
        m_item->getHeight() = event->pos().y() - m_item->getYPos();
        m_item->getXPos() = event->pos().x();

    } else if (m_corner == TOPRIGHT) {
        m_item->getWidth() = event->pos().x() - m_item->getXPos();
        m_item->getHeight() = m_item->getYPos() + m_item->getHeight() - event->pos().y();
        m_item->getYPos() = event->pos().y();
    }

    else if (m_corner == BOTTOMRIGHT) {
        m_item->getWidth() = event->pos().x() - m_item->getXPos();
        m_item->getHeight() = event->pos().y() - m_item->getYPos();
    }
}

qreal RectangleView::calculateRotation(QGraphicsSceneMouseEvent *event)
{
    qreal lengthOfHypotenuse = sqrt(pow(m_item->getWidth() / 2, 2) + pow(m_item->getHeight() / 2, 2));
    qreal offsetAngle = acos((m_item->getWidth() / 2) / lengthOfHypotenuse) * 180 / M_PI;
    qreal radians = atan(
        (event->scenePos().y() - this->mapToScene(m_item->getXPos() + m_item->getWidth() / 2, m_item->getYPos() + m_item->getHeight() / 2).y())
        / (event->scenePos().x()
           - this->mapToScene(m_item->getXPos() + m_item->getWidth() / 2, m_item->getYPos() + m_item->getHeight() / 2).x()));

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

void RectangleView::setWidth(qreal width)
{
    m_item->getWidth() = width;
}

void RectangleView::setHeigth(qreal heigth)
{
    m_item->getHeight() = heigth;
}

void RectangleView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setFlag(QGraphicsItem::ItemIsMovable, false);

    //if one of the corners is clicked then go in to resize Mode
    if (event->button() == Qt::LeftButton && getTopLeftCorner().contains(event->pos())) {
        m_item->setResizeMode(true);
        m_corner = TOPLEFT;
        setCursor(Qt::SizeFDiagCursor);

    } else if (event->button() == Qt::LeftButton && getBottomLeftCorner.contains(event->pos())) {
        m_item->setResizeMode(true);
        m_corner = BOTTOMLEFT;
        setCursor(Qt::SizeBDiagCursor);

    } else if (event->button() == Qt::LeftButton && getTopRightCorner().contains(event->pos())) {
        m_item->setResizeMode(true);
        m_corner = TOPRIGHT;
        setCursor(Qt::SizeBDiagCursor);
    }

    else if (event->button() == Qt::LeftButton && getBottomRightCorner().contains(event->pos())) {
        m_item->setResizeMode(true);
        m_corner = BOTTOMRIGHT;
        setCursor(Qt::SizeFDiagCursor);

    // process as usual
    } else {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mousePressEvent(event);
    }
}

void RectangleView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //check which mode is active and process with the active mode
    if (m_corner != NONE && m_item->isResizeMode()) {
        calculateResize(event);

    } else if (m_corner != NONE && m_item->isRotationMode()) {
        QTransform transform;
        transform.translate(m_item->getXPos() + m_item->getWidth() * 0.5, m_item->getYPos() + m_item->getHeight() * 0.5);
        transform.rotate(calculateRotation(event));
        transform.translate(-(m_item->getXPos() + m_item->getWidth() * 0.5), -(m_item->getYPos() + m_item->getHeight() * 0.5));
        setTransform(transform);

    // process as usual
    } else {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void RectangleView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // set all modes off, change cursor and process as usual
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    m_item->setResizeMode(false);
    m_item->setRotationMode(false);
    setCursor(Qt::ArrowCursor);
    QGraphicsItem::mouseReleaseEvent(event);
}

void RectangleView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    //activate rotation mode
    if (event->button() == Qt::LeftButton && getTopLeftCorner().contains(event->pos())) {
        m_item->setRotationMode(true);
        m_corner = TOPLEFT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::ClosedHandCursor);

    } else if (event->button() == Qt::LeftButton && getBottomLeftCorner.contains(event->pos())) {
        m_item->setRotationMode(true);
        m_corner = BOTTOMLEFT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::ClosedHandCursor);

    } else if (event->button() == Qt::LeftButton && getTopRightCorner().contains(event->pos())) {
        m_item->setRotationMode(true);
        m_corner = TOPRIGHT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::ClosedHandCursor);
    }

    else if (event->button() == Qt::LeftButton && getBottomRightCorner().contains(event->pos())) {
        m_item->setRotationMode(true);
        m_corner = BOTTOMRIGHT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::ClosedHandCursor);

    } else {
        m_item->setRotationMode(false);
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mouseDoubleClickEvent(event);
    }
}

void RectangleView::setInclude()
{
    m_color = INCLUDE;
    update();
}

void RectangleView::setExclude()
{
    m_color = EXCLUDE;
    update();
}

QRectF RectangleView::getTopLeftCorner()
{
    return QRectF(m_item->m_item->getXPos()- 5, m_item->getYPos() - 5, 10, 10);
}

QRectF RectangleView::getTopRightCorner()
{
    return QRectF(m_item->getXPos() + m_item->getWidth() - 5,  m_item->getYPos() - 5, 10, 10);
}

QRectF RectangleView::getBottomLeftCorner()
{
    return QRectF(m_item->getXPos() + m_item->getWidth() - 5,  m_item->getYPos() - 5, 10, 10);
}

QRectF RectangleView::getBottomRightCorner()
{
    return QRectF(m_item->getXPos() + m_item->getWidth() - 5,  m_item->getYPos() + m_item->getHeight() - 5, 10, 10);
}

void RectangleView::setItem(RectangleItem item)
{
    m_item = item;
}
