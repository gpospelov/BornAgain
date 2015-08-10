#include "RectangleView.h"
#include "RectangleItem.h"
#include "ParameterizedItem.h"
#include "DesignerHelper.h"
#include "RotationArrow.h"
#include "ResizeArrow.h"
#include <QPainterPath>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <cmath>
#include <QCursor>

static const qreal widthAndHeight = 5;
static const qreal OffsetPosition = 2.5;


RectangleView::RectangleView()
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
    connect(this, SIGNAL(xChanged()), this, SLOT(onChangedX()));
    connect(this, SIGNAL(yChanged()), this, SLOT(onChangedY()));
}

void RectangleView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // paint rectangle
    painter->setRenderHints(QPainter::Antialiasing);
    prepareGeometryChange();

    QRectF rectangle(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal(),
                m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal(),
                m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal(),
                m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal());
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if (m_item->getRegisteredProperty(RectangleItem::P_COLOR).toInt() == 0) {
        brush.setColor(DesignerHelper::getDefaultColor("Transparant red"));
        painter->setPen(brush.color().darker());
        painter->setBrush(brush);
        painter->drawRect(rectangle);

    } else {
        brush.setColor(DesignerHelper::getDefaultColor("Transparant blue"));
        painter->setPen(brush.color().darker());
        painter->setBrush(brush);
        painter->drawRect(rectangle);
    }

    // paint rectangles on corners if this item is selected
    if (this->isSelected()) {
        painter->setBrush(painter->pen().color());
        painter->drawRect(getTopLeftCorner());
        painter->drawRect(getBottomLeftCorner());
        painter->drawRect(getTopRightCorner());
        painter->drawRect(getBottomRightCorner());
    }

        updateRotationArrows();
}

QRectF RectangleView::boundingRect() const
{
        return QRectF(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal() -5,
                      m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() -5,
                      m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() + 10,
                      m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() + 10);
}

void RectangleView::checkResizeRules(QGraphicsSceneMouseEvent *event)
{
    if (m_corner == TOPLEFT) {
        if (m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal() +
                m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() <= event->pos().x()) {
            m_corner = TOPRIGHT;
            setCursor(Qt::SizeBDiagCursor);

        } else if (m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal()
                   + m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal()
                   <= event->pos().y()) {
            m_corner = BOTTOMLEFT;
            setCursor(Qt::SizeBDiagCursor);
        }
    } else if (m_corner == TOPRIGHT) {
        if (event->pos().x() <= m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal()) {
            m_corner = TOPLEFT;
            setCursor(Qt::SizeFDiagCursor);

        } else if (m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal()
                   + m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal()
                   <= event->pos().y()) {
            m_corner = BOTTOMRIGHT;
            setCursor(Qt::SizeFDiagCursor);
        }
    } else if (m_corner == BOTTOMLEFT) {
        if (m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal()
                + m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() <= event->pos().x()) {
            m_corner = BOTTOMRIGHT;
            setCursor(Qt::SizeFDiagCursor);

        } else if (event->pos().y() <= m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal()) {
            m_corner = TOPLEFT;
            setCursor(Qt::SizeFDiagCursor);
        }
    } else if (m_corner == BOTTOMRIGHT) {
        if (event->pos().x() <= m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal()) {
            m_corner = BOTTOMLEFT;
            setCursor(Qt::SizeBDiagCursor);

        } else if (event->pos().y() <= m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal()) {
            m_corner = TOPRIGHT;
            setCursor(Qt::SizeBDiagCursor);
        }
    }
}

void RectangleView::calculateResize(QGraphicsSceneMouseEvent *event)
{
    checkResizeRules(event);
    if (m_corner == TOPLEFT) {
        m_item->setRegisteredProperty(RectangleItem::P_WIDTH,
                                      m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal()
                                      + m_item->getRegisteredProperty(RectangleItem::P_WIDTH).
                                      toReal() - event->pos().x());

        m_item->setRegisteredProperty(RectangleItem::P_HEIGHT,
                                      m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal()
                                      + m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).
                                      toReal() - event->pos().y());

        m_item->setRegisteredProperty(RectangleItem::P_POSX, event->pos().x());
        m_item->setRegisteredProperty(RectangleItem::P_POSY, event->pos().y());

    }
    else if (m_corner == BOTTOMLEFT) {
        m_item->setRegisteredProperty(RectangleItem::P_WIDTH,
                                      m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal()
                                      + m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal()
                                      - event->pos().x());
        m_item->setRegisteredProperty(RectangleItem::P_HEIGHT, event->pos().y()
                                      - m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal());
        m_item->setRegisteredProperty(RectangleItem::P_POSX, event->pos().x());

    }
    else if (m_corner == TOPRIGHT) {
        m_item->setRegisteredProperty(RectangleItem::P_WIDTH, event->pos().x()
                                      - m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal());
        m_item->setRegisteredProperty(RectangleItem::P_HEIGHT,
                                      m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal()
                                      + m_item->getRegisteredProperty(RectangleItem::P_HEIGHT)
                                      .toReal() - event->pos().y());
        m_item->setRegisteredProperty(RectangleItem::P_POSY, event->pos().y());
    }
    else if (m_corner == BOTTOMRIGHT) {
        m_item->setRegisteredProperty(RectangleItem::P_WIDTH, event->pos().x()
                                      - m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal());
        m_item->setRegisteredProperty(RectangleItem::P_HEIGHT, event->pos().y()
                                      - m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal());
    }
}

qreal RectangleView::getRotationAngle(QGraphicsSceneMouseEvent *event)
{
    QPointF middlePoint
        = mapToScene(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal()
                     + m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() / 2,
                     m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal()
                     + m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() / 2);
    qreal lengthOfHypotenuse
        = sqrt(pow(m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() / 2, 2)
               + pow(m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() / 2, 2));
    qreal offsetAngle = acos((m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() / 2)
                             / lengthOfHypotenuse) * 180 / M_PI;
    qreal radians = atan((event->scenePos().y() - middlePoint.y())
                         / (event->scenePos().x() - middlePoint.x()));

    if (m_corner == TOPLEFT) {
        m_item->setRegisteredProperty(RectangleItem::P_ANGLE, radians * 180 / M_PI - offsetAngle);
        return radians * 180 / M_PI - offsetAngle;

    } else if (m_corner == TOPRIGHT) {
        m_item->setRegisteredProperty(RectangleItem::P_ANGLE, radians * 180 / M_PI + offsetAngle - 180);
        return radians * 180 / M_PI + offsetAngle - 180;

    } else if (m_corner == BOTTOMLEFT) {
        m_item->setRegisteredProperty(RectangleItem::P_ANGLE, radians * 180 / M_PI + offsetAngle - 180);
        return  radians * 180 / M_PI + offsetAngle - 180;

    } else if (m_corner == BOTTOMRIGHT) {
        m_item->setRegisteredProperty(RectangleItem::P_ANGLE, radians * 180 / M_PI - offsetAngle);
        return radians * 180 / M_PI - offsetAngle;
    }
    return 0.0;
}

void RectangleView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setFlag(QGraphicsItem::ItemIsMovable, false);

    if (event->button() == Qt::LeftButton) {
        setSelectedCorner(event->pos());

        if (m_corner == NONE) {
            this->setFlag(QGraphicsItem::ItemIsMovable, true);
            m_block_mode = false;
            QGraphicsItem::mousePressEvent(event);
        }
    }

}

void RectangleView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // check which mode is active and process with the active mode
    if (m_mode == RESIZE && m_corner != NONE) {
        calculateResize(event);
        m_block_mode = true;
    } else if (m_corner != NONE && m_mode == ROTATION) {
        QTransform transform;
        transform.translate(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal()
                            + m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() * 0.5,
                            m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal()
                            + m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() * 0.5);
        getRotationAngle(event);
        transform.rotate(m_item->getRegisteredProperty(RectangleItem::P_ANGLE).toReal());
        transform.translate(-(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal()
                              + m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() * 0.5),
                            -(m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal()
                              + m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() * 0.5));
        setTransform(transform);
        m_block_mode = true;

//         process as usual
    } else {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        m_block_mode = false;
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void RectangleView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_block_mode && m_corner == NONE) {
        if ((m_mode == RESIZE)) {
            m_mode = ROTATION;
        } else if ((m_mode == ROTATION)) {
            m_mode = RESIZE;
        }
    }
    m_block_mode = false;
    m_corner = NONE;
    setCursor(Qt::ArrowCursor);
    QGraphicsItem::mouseReleaseEvent(event);
}

void RectangleView::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    setSelectedCorner(event->pos());
    m_corner = NONE;
}

void RectangleView::setInclude()
{
    m_item->setRegisteredProperty(RectangleItem::P_COLOR, 0);
}

void RectangleView::setExclude()
{
    m_item->setRegisteredProperty(RectangleItem::P_COLOR, 1);
}


QRectF RectangleView::getTopLeftCorner()
{
    return QRectF(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal() - OffsetPosition,
                  m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() - OffsetPosition,
                  widthAndHeight, widthAndHeight);
}

QRectF RectangleView::getTopRightCorner()
{
    return QRectF(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal()
                  + m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() - OffsetPosition,
                  m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() - OffsetPosition,
                  widthAndHeight, widthAndHeight);
}

QRectF RectangleView::getBottomLeftCorner()
{
    return QRectF(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal() - OffsetPosition,
                  m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal()
                  + m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() - OffsetPosition,
                  widthAndHeight, widthAndHeight);
}

QRectF RectangleView::getBottomRightCorner()
{
    return QRectF(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal()
                  + m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() - OffsetPosition,
                  m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal()
                  + m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() - OffsetPosition,
                  widthAndHeight, widthAndHeight);
}

void RectangleView::setParameterizedItem(ParameterizedItem *item)
{
    m_item = item;
//    setX(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal());
//    setY(m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal());
    setRotation(m_item->getRegisteredProperty(RectangleItem::P_ANGLE).toReal());
    connect(m_item, SIGNAL(propertyChanged(const QString &)), this,
            SLOT(onPropertyChange(const QString &)));
    initializeArrow();
}

void RectangleView::onChangedX()
{
    m_block_mode = true;
}

void RectangleView::onChangedY()
{
    m_block_mode = true;
}

void RectangleView::onPropertyChange(const QString &propertyName)
{
    if(propertyName == RectangleItem::P_POSX) {
         m_block_mode = true;
    }
    else if(propertyName == RectangleItem::P_POSY) {
         m_block_mode = true;
    }
    else if(propertyName == RectangleItem::P_ANGLE) {
    QTransform transform;
    transform.translate(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal()
                        + m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() * 0.5,
                        m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal()
                        + m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() * 0.5);
    transform.rotate(m_item->getRegisteredProperty(RectangleItem::P_ANGLE).toReal());
    transform.translate(-(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal()
                          + m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() * 0.5),
                        -(m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal()
                          + m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() * 0.5));
    setTransform(transform);
    }
}

ParameterizedItem *RectangleView::getParameterizedItem()
{
    return m_item;
}

void RectangleView::setSelectedCorner(QPointF currentMousePosition)
{
    if (getTopLeftCorner().contains(currentMousePosition)) {
        qDebug() << "TOPLEFT";
        m_corner = TOPLEFT;
        if(m_mode == RESIZE)
            setCursor(Qt::SizeFDiagCursor);
    } else if (getTopRightCorner().contains(currentMousePosition)) {
        qDebug() << "TOPRIGHT";
        m_corner = TOPRIGHT;
        if(m_mode == RESIZE)
            setCursor(Qt::SizeBDiagCursor);
    } else if (getBottomLeftCorner().contains(currentMousePosition)) {
        qDebug() << "BOTTOMLEFT";
        m_corner = BOTTOMLEFT;
        if(m_mode == RESIZE)
            setCursor(Qt::SizeBDiagCursor);
    } else if (getBottomRightCorner().contains(currentMousePosition)) {
        qDebug() << "BOTTOMRIGHT";
        m_corner = BOTTOMRIGHT;
        if(m_mode == RESIZE)
            setCursor(Qt::SizeFDiagCursor);
    } else {
        m_corner = NONE;
        setCursor(QCursor());
    }

    if (m_mode == ROTATION && m_corner != NONE) {
        setCursor(QCursor(QPixmap(":/images/rotationArrow.png")));
    }
}

void RectangleView::updateRotationArrows()
{
    // 0 - 3 are rotation arrows
    childItems()[0]->setPos(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal(),
                            m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal());

    childItems()[1]->setPos(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal() +
                          m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal(),
                          m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal());

    childItems()[2]->setPos(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal(),
                          m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() +
                          m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal());

    childItems()[3]->setPos(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal() +
                            m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal(),
                            m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() +
                            m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal());

    // 4 - 7 are resize arrows
    childItems()[4]->setPos(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal(),
                            m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal());

    childItems()[5]->setPos(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal() +
                          m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal(),
                          m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal());

    childItems()[6]->setPos(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal(),
                          m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() +
                          m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal());

    childItems()[7]->setPos(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal() +
                            m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal(),
                            m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() +
                            m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal());


    if(isSelected() == false) {
        for(int i = 0; i < childItems().length(); ++i) {
            childItems()[i]->setVisible(false);
        }

    }
    else if(m_mode == RESIZE) {
        for(int i = 0; i < childItems().length(); ++i) {
            if(i < 4) {
                childItems()[i]->setVisible(false);
            }
            else {
                childItems()[i]->setVisible(true);
            }
        }
    }    else if(m_mode == ROTATION) {
        for(int i = 0; i < childItems().length(); ++i) {
            if(i < 4) {
                childItems()[i]->setVisible(true);
            }
            else {
                childItems()[i]->setVisible(false);
            }
        }
    }
}

void RectangleView::initializeArrow()
{
    RotationArrow *topLeftRotationArrow = new RotationArrow(this);
    RotationArrow *topRightRotationArrow = new RotationArrow(this);
    RotationArrow *bottomLeftRotationArrow = new RotationArrow(this);
    RotationArrow *bottomRightRotationArrow = new RotationArrow(this);

    ResizeArrow *topLeftResizeArrow = new ResizeArrow(this);
    ResizeArrow *topRightResizeArrow = new ResizeArrow(this);
    ResizeArrow *bottomLeftResizeArrow = new ResizeArrow(this);
    ResizeArrow *bottomRightResizeArrow = new ResizeArrow(this);




    topLeftRotationArrow->setPos(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal(),
                         m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal());

    topRightRotationArrow->setRotation(90);
    topRightRotationArrow->setPos(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal() +
                          m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal(),
                          m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() +
                          m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal());

    bottomLeftRotationArrow->setRotation(270);
    bottomLeftRotationArrow->setPos(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal(),
                            m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() +
                            m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal());

    bottomRightRotationArrow->setRotation(180);
    bottomLeftRotationArrow->setPos(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal() +
                            m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal(),
                            m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() +
                            m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal());


    topLeftResizeArrow->setPos(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal(),
                         m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal());

    topRightResizeArrow->setRotation(90);
    topRightResizeArrow->setPos(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal() +
                          m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal(),
                          m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() +
                          m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal());

    bottomLeftResizeArrow->setRotation(270);
    bottomLeftResizeArrow->setPos(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal(),
                            m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() +
                            m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal());

    bottomRightResizeArrow->setRotation(180);
    bottomLeftResizeArrow->setPos(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal() +
                            m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal(),
                            m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() +
                            m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal());



    topRightRotationArrow->setVisible(false);
    topLeftRotationArrow->setVisible(false);
    bottomLeftRotationArrow->setVisible(false);
    bottomRightRotationArrow->setVisible(false);

    topRightResizeArrow->setVisible(false);
    topLeftResizeArrow->setVisible(false);
    bottomLeftResizeArrow->setVisible(false);
    bottomRightResizeArrow->setVisible(false);
}



