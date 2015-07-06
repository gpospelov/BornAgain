#include "RectangleView.h"
#include "RectangleItem.h"
#include "ParameterizedItem.h"
#include "DesignerHelper.h"
#include "RotationArrow.h"
#include <QPainterPath>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <cmath>
#include <QCursor>

RectangleView::RectangleView()
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable, true);
}

void RectangleView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // paint rectangle
    painter->setRenderHints(QPainter::Antialiasing);
    this->prepareGeometryChange();
    if (m_item->getRegisteredProperty(RectangleItem::P_COLOR).toInt() == 0) {
        QBrush transRed(DesignerHelper::getDefaultColor("Transparant red"));
        painter->fillRect(0, 0, m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal(),
                          m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal(),
                          transRed);
    } else {
        QBrush transBlue(DesignerHelper::getDefaultColor("Transparant blue"));
        painter->fillRect(0, 0, m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal(),
                          m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal(),
                          transBlue);
    }

    // paint corner rectangles only if this item is selected
    if (this->isSelected()) {
        painter->setBrush(Qt::green);
        painter->drawRect(getTopLeftCorner());
        painter->drawRect(getBottomLeftCorner());
        painter->drawRect(getTopRightCorner());
        painter->drawRect(getBottomRightCorner());
    }
//    showRotationArrows();
}

// FIXME Let's discuss this method, too much to type to explain

QRectF RectangleView::boundingRect() const
{
    if(m_item != NULL) {
        double width = m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() + 10;
        double height = m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() + 10;
        return QRectF(0 - 5, 0 - 5, m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() + 10,
                      m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() + 10);
    }
    else {
        return QRectF(0,0,0,0);
    }
}

// FIXME refactor this or explain me what is going on  here
void RectangleView::checkResizeRules(QGraphicsSceneMouseEvent *event)
{
    if (m_corner == TOPLEFT) {
        if (m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() <= event->pos().x()) {
            m_corner = TOPRIGHT;
            setCursor(Qt::SizeBDiagCursor);

        } else if (m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal()
                   <= event->pos().y()) {
            m_corner = BOTTOMLEFT;
            setCursor(Qt::SizeBDiagCursor);
        }
    } else if (m_corner == TOPRIGHT) {
        if (event->pos().x() <= 0) {
            m_corner = TOPLEFT;
            setCursor(Qt::SizeFDiagCursor);

        } else if (m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal()
                   <= event->pos().y()) {
            m_corner = BOTTOMRIGHT;
            setCursor(Qt::SizeFDiagCursor);
        }
    } else if (m_corner == BOTTOMLEFT) {
        if (m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() <= event->pos().x()) {
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

// FIXME refactor this or explain me what is going on  here
void RectangleView::calculateResize(QGraphicsSceneMouseEvent *event)
{
    checkResizeRules(event);

    if (m_corner == TOPLEFT) {
        m_item->setRegisteredProperty(RectangleItem::P_WIDTH,
                                      std::abs(m_item->getRegisteredProperty(RectangleItem::P_WIDTH)
                                                   .toReal() - event->pos().x()));
        m_item->setRegisteredProperty(
            RectangleItem::P_HEIGHT, std::abs(m_item->getRegisteredProperty(RectangleItem::P_HEIGHT)
                                                  .toReal() - event->pos().y()));
        this->setX(event->scenePos().x());
        this->setY(event->scenePos().y());

    } else if (m_corner == BOTTOMLEFT) {
        m_item->setRegisteredProperty(
            RectangleItem::P_WIDTH,
            std::abs(x() + m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal()
                     - event->scenePos().x()));
        m_item->setRegisteredProperty(RectangleItem::P_HEIGHT,
                                      std::abs(event->scenePos().y() - y()));
        this->setX(event->scenePos().x());

    } else if (m_corner == TOPRIGHT) {
        m_item->setRegisteredProperty(RectangleItem::P_WIDTH,
                                      std::abs(event->scenePos().x() - x()));
        m_item->setRegisteredProperty(
            RectangleItem::P_HEIGHT,
            std::abs(y() + m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal()
                     - event->scenePos().y()));
        this->setY(event->scenePos().y());
    }

    else if (m_corner == BOTTOMRIGHT) {
        m_item->setRegisteredProperty(RectangleItem::P_WIDTH, event->pos().x());
        m_item->setRegisteredProperty(RectangleItem::P_HEIGHT, event->pos().y());
    }
}

qreal RectangleView::getRotationAngle(QGraphicsSceneMouseEvent *event)
{
    QPointF middlePoint
        = mapToScene(m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() / 2,
                     m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() / 2);
    qreal lengthOfHypotenuse
        = sqrt(pow(m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() / 2, 2)
               + pow(m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() / 2, 2));
    qreal offsetAngle = acos((m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() / 2)
                             / lengthOfHypotenuse) * 180 / M_PI;
    qreal radians = atan((event->scenePos().y() - middlePoint.y())
                         / (event->scenePos().x() - middlePoint.x()));

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

    if (event->button() == Qt::LeftButton) {
        setSelectedCorner(event);

        if (m_corner == NONE) {
            if ((m_mode == RESIZE)) {
                m_mode = ROTATION;
            } else if ((m_mode == ROTATION)) {
                m_mode = RESIZE;
            }
            this->setFlag(QGraphicsItem::ItemIsMovable, true);
            QGraphicsItem::mousePressEvent(event);
        }
    }
}

void RectangleView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "RectangleView::mouseMoveEvent()";
    // check which mode is active and process with the active mode
    if (m_mode == RESIZE && m_corner != NONE) {
        calculateResize(event);
    } else if (m_corner != NONE && m_mode == ROTATION) {
        QTransform transform;
        transform.translate(m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() * 0.5,
                            m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() * 0.5);
        transform.rotate(getRotationAngle(event));
        transform.translate(
            -(m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() * 0.5),
            -(m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() * 0.5));
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
    //    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    //    m_mode = SELECTION;
    m_corner = NONE;
    setCursor(Qt::ArrowCursor);
    QGraphicsItem::mouseReleaseEvent(event);
}

void RectangleView::setInclude()
{
    m_item->setRegisteredProperty(RectangleItem::P_COLOR, 0);
}

void RectangleView::setExclude()
{
    m_item->setRegisteredProperty(RectangleItem::P_COLOR, 1);
}

// FIXME Remove 5,10 hardoced values, what if I want smaller rectangles?
//       I have to be able to replace numbers in one place

QRectF RectangleView::getTopLeftCorner()
{
    return QRectF(0 - 5, 0 - 5, 10, 10);
}

QRectF RectangleView::getTopRightCorner()
{
    return QRectF(0 + m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() - 5, 0 - 5, 10,
                  10);
}

QRectF RectangleView::getBottomLeftCorner()
{
    return QRectF(0 - 5, 0 + m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() - 5,
                  10, 10);
}

QRectF RectangleView::getBottomRightCorner()
{
    return QRectF(0 + m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() - 5,
                  0 + m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() - 5, 10, 10);
}

void RectangleView::setParameterizedItem(ParameterizedItem *item)
{
    m_item = item;
    setX(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal() - 5);
    setY(m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() - 5);
    connect(m_item, SIGNAL(propertyChanged(const QString &)), this,
            SLOT(onPropertyChange(const QString &)));
}

void RectangleView::onChangedX()
{
    m_block_update = true;
    qDebug() << "onXValueChanged(double xValue)-> x value changed" << x()
             << m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal();
    m_item->setRegisteredProperty(RectangleItem::P_POSX, x());
    m_block_update = false;
}

void RectangleView::onChangedY()
{
    m_block_update = true;
    qDebug() << "onYValueChanged(double yValue)-> y value changed" << y()
             << m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal();
    m_item->setRegisteredProperty(RectangleItem::P_POSY, y());
    m_block_update = false;
}

void RectangleView::onPropertyChange(const QString &propertyName)
{
    if (m_block_update)
        return;
    qDebug() << "void EllipseView::onPropertyChange(const QString &propertyName)"
             << m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal()
             << m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal()
             << m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal()
             << m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal();

    if (propertyName == RectangleItem::P_POSX) {
        setX(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal() + 5);
    } else if (propertyName == RectangleItem::P_POSY) {
        setY(m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() + 5);
    }
}

ParameterizedItem *RectangleView::getParameterizedItem()
{
    return m_item;
}

void RectangleView::setSelectedCorner(QGraphicsSceneMouseEvent *event)
{
    if (getTopLeftCorner().contains(event->pos())) {
        qDebug() << "TOPLEFT";
        m_corner = TOPLEFT;
        setCursor(Qt::SizeFDiagCursor);
    } else if (getTopRightCorner().contains(event->pos())) {
        qDebug() << "TOPRIGHT";
        m_corner = TOPRIGHT;
        setCursor(Qt::SizeBDiagCursor);
    } else if (getBottomLeftCorner().contains(event->pos())) {
        qDebug() << "BOTTOMLEFT";
        m_corner = BOTTOMLEFT;
        setCursor(Qt::SizeBDiagCursor);
    } else if (getBottomRightCorner().contains(event->pos())) {
        qDebug() << "BOTTOMRIGHT";
        m_corner = BOTTOMRIGHT;
        setCursor(Qt::SizeFDiagCursor);
    } else {
        m_corner = NONE;
    }

    if (m_mode == ROTATION) {
        setCursor(Qt::ClosedHandCursor);
    }
}

void RectangleView::showRotationArrows()
{
    RotationArrow *topLeftArrow = new RotationArrow(this);
    RotationArrow *topRightArrow = new RotationArrow(this);
    topRightArrow->setRotation(90);
    topRightArrow->setPos(0,m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal());
}
