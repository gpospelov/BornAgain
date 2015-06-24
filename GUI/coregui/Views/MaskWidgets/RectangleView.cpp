
#include "RectangleView.h"
#include "RectangleItem.h"
#include <iostream>
#include <cmath>
#include "ParameterizedItem.h"


// FIXME

RectangleView::RectangleView()
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIgnoresTransformations, false);
    disconnect(this, SIGNAL(xChanged()), this, SLOT(onChangedX()));
    disconnect(this, SIGNAL(yChanged()), this, SLOT(onChangedY()));
    connect(this, SIGNAL(xChanged()), this, SLOT(onXValueChanged()));
    connect(this, SIGNAL(yChanged()), this, SLOT(onYValueChanged()));
}

void RectangleView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    // paint rectangle
    painter->setRenderHints(QPainter::Antialiasing);
    this->prepareGeometryChange();
    if(m_item->getColor() == 0) {
        QBrush transRed(QColor(0xFF, 0, 0, 0x80));
        painter->fillRect(0, 0, m_item->getWidth(), m_item->getHeight(),transRed);
    }
    else {
        QBrush transBlue(QColor(0, 0, 0xFF, 0x80));
        painter->fillRect(0, 0, m_item->getWidth(), m_item->getHeight(),transBlue);
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
    return QRectF(0 - 10, 0 - 10, m_item->getWidth() + 20,  m_item->getHeight() + 20);
}

void RectangleView::checkResizeRules(QGraphicsSceneMouseEvent *event)
{
    if (m_corner == TOPLEFT) {
        if (m_item->getWidth() <= event->pos().x()) {
            m_corner = TOPRIGHT;
            setCursor(Qt::SizeBDiagCursor);

        } else if (m_item->getHeight() <= event->pos().y()) {
            m_corner = BOTTOMLEFT;
            setCursor(Qt::SizeBDiagCursor);
        }
    } else if (m_corner == TOPRIGHT) {
        if (event->pos().x() <= 0) {
            m_corner = TOPLEFT;
            setCursor(Qt::SizeFDiagCursor);

        } else if (m_item->getHeight() <= event->pos().y()) {
            m_corner = BOTTOMRIGHT;
            setCursor(Qt::SizeFDiagCursor);
        }
    } else if (m_corner == BOTTOMLEFT) {
        if (m_item->getWidth() <= event->pos().x()) {
            m_corner = BOTTOMRIGHT;
            setCursor(Qt::SizeFDiagCursor);

        } else if (event->pos().y() <= 0) {
            m_corner = TOPLEFT;
            setCursor(Qt::SizeFDiagCursor);
        }
    } else if (m_corner == BOTTOMRIGHT) {
        if (event->pos().x() <= 0) {
            m_corner = BOTTOMLEFT;
            setCursor(Qt::SizeBDiagCursor);

        } else if (event->pos().y() <= 0) {
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
        m_item->setWidth(m_item->getWidth() - event->pos().x());
        m_item->setHeight(m_item->getHeight() - event->pos().y());
        this->setX(event->scenePos().x());
        this->setY(event->scenePos().y());

    } else if (m_corner == BOTTOMLEFT) {
        m_item->setWidth(x() + m_item->getWidth() - event->scenePos().x());
        m_item->setHeight(event->scenePos().y() - y());
        this->setX(event->scenePos().x());


    } else if (m_corner == TOPRIGHT) {
        m_item->setWidth(event->scenePos().x() - x());
        m_item->setHeight(y() + m_item->getHeight() - event->scenePos().y());
        this->setY(event->scenePos().y());
    }

    else if (m_corner == BOTTOMRIGHT) {
        m_item->setWidth(event->pos().x());
        m_item->setHeight(event->pos().y());
    }
}

qreal RectangleView::calculateRotation(QGraphicsSceneMouseEvent *event)
{
    QPointF middlePoint =  mapToScene(m_item->getWidth()/2, m_item->getHeight()/2);
    qreal lengthOfHypotenuse = sqrt(pow(m_item->getWidth() / 2, 2) + pow(m_item->getHeight() / 2, 2));
    qreal offsetAngle = acos((m_item->getWidth() / 2) / lengthOfHypotenuse) * 180 / M_PI;
    qreal radians = atan((event->scenePos().y() - middlePoint.y()) / (event->scenePos().x() - middlePoint.x()));

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


void RectangleView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setFlag(QGraphicsItem::ItemIsMovable, false);

    //if one of the corners is clicked then go in to resize Mode
    if (event->button() == Qt::LeftButton && getTopLeftCorner().contains(event->pos())) {
        m_item->setResizeMode(true);
        m_corner = TOPLEFT;
        setCursor(Qt::SizeFDiagCursor);

    } else if (event->button() == Qt::LeftButton && getBottomLeftCorner().contains(event->pos())) {
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
        transform.translate(m_item->getWidth() * 0.5,  m_item->getHeight() * 0.5);
        transform.rotate(calculateRotation(event));
        transform.translate(-(m_item->getWidth() * 0.5), -(m_item->getHeight() * 0.5));
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
        m_item->setResizeMode(false);
        m_item->setRotationMode(true);
        m_corner = TOPLEFT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::ClosedHandCursor);

    } else if (event->button() == Qt::LeftButton && getBottomLeftCorner().contains(event->pos())) {
        m_item->setResizeMode(false);
        m_item->setRotationMode(true);
        m_corner = BOTTOMLEFT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::ClosedHandCursor);

    } else if (event->button() == Qt::LeftButton && getTopRightCorner().contains(event->pos())) {
        m_item->setResizeMode(false);
        m_item->setRotationMode(true);
        m_corner = TOPRIGHT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::ClosedHandCursor);
    }

    else if (event->button() == Qt::LeftButton && getBottomRightCorner().contains(event->pos())) {
        m_item->setResizeMode(false);
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
    m_item->setColor(0);
}

void RectangleView::setExclude()
{
    m_item->setColor(1);
}

QRectF RectangleView::getTopLeftCorner()
{
    return QRectF(0 - 5, 0 - 5, 10, 10);
}

QRectF RectangleView::getTopRightCorner()
{
    return QRectF(0 + m_item->getWidth() - 5, 0  - 5, 10, 10);
}

QRectF RectangleView::getBottomLeftCorner()
{
    return QRectF(0 - 5, 0  + m_item->getHeight() - 5, 10, 10);
}

QRectF RectangleView::getBottomRightCorner()
{
    return QRectF(0 + m_item->getWidth() - 5, 0  + m_item->getHeight() - 5, 10, 10);
}

void RectangleView::setItem(ParameterizedItem *item)
{
    m_item = dynamic_cast<RectangleItem *>(item);
    setX(m_item->getXPos() - 10);
    setY(m_item->getYPos() - 10);
    connect(m_item, SIGNAL(propertyChanged(const QString &)), this, SLOT(onPropertyChange(const QString &)));
}

void RectangleView::onXValueChanged()
{
    m_block_update = true;
    qDebug() << "onXValueChanged(double xValue)-> x value changed" << x();
    m_item->setXPos(x() + 10);
    m_block_update = false;
}

void RectangleView::onYValueChanged()
{
    m_block_update = true;
    qDebug() << "onYValueChanged(double yValue)-> y value changed" << y();
    m_item->setYPos(y() + 10);
    m_block_update = false;

}


void RectangleView::onPropertyChange(const QString &propertyName)
{
    if(m_block_update) return;
       qDebug() << "void RectangleView::onPropertyChange(const QString &propertyName)";
       if(propertyName == RectangleItem::P_POSX) {
           setX(m_item->getXPos() - 10);
       } else if(propertyName == RectangleItem::P_POSY) {
           setY(m_item->getYPos() - 10);
       }
}

ParameterizedItem *RectangleView::getParameterizedItem()
{
    return m_item;
}
