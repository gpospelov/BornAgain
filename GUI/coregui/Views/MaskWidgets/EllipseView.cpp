#include "EllipseView.h"
#include "EllipseItem.h"
#include "ParameterizedItem.h"
#include "RotationArrow.h"
#include "ResizeArrow.h"
#include <cmath>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QDebug>

static const qreal widthAndHeight = 5;
static const qreal OffsetPosition = 2.5;

EllipseView::EllipseView()
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
}

void EllipseView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    // paint ellipse
    painter->setRenderHints(QPainter::Antialiasing);
    this->prepareGeometryChange();

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if (m_item->getRegisteredProperty(EllipseItem::P_COLOR).toBool() == 0) {
        brush.setColor(DesignerHelper::getDefaultColor("Transparant red"));
        painter->setPen(brush.color().darker());
        painter->setBrush(brush);
        painter->drawEllipse(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal(),
                             m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal(),
                             m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal(),
                             m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal());
    } else {
        brush.setColor(DesignerHelper::getDefaultColor("Transparant blue"));
        painter->setPen(brush.color().darker());
        painter->setBrush(brush);
        painter->drawEllipse(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal(),
                             m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal(),
                             m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal(),
                             m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal());
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

QRectF EllipseView::boundingRect() const
{
    return QRectF(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal() - 5,
                  m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal() - 5,
                  m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() + 10,
                  m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() + 10);
}

void EllipseView::checkResizeRules(QGraphicsSceneMouseEvent *event)
{
    if (m_corner == TOPLEFT) {
        if (m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal() +
                m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() <= event->pos().x()) {
            m_corner = TOPRIGHT;
            setCursor(Qt::SizeBDiagCursor);

        } else if (m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                   + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal()
                   <= event->pos().y()) {
            m_corner = BOTTOMLEFT;
            setCursor(Qt::SizeBDiagCursor);
        }
    } else if (m_corner == TOPRIGHT) {
        if (event->pos().x() <= m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()) {
            m_corner = TOPLEFT;
            setCursor(Qt::SizeFDiagCursor);

        } else if (m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                   + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal()
                   <= event->pos().y()) {
            m_corner = BOTTOMRIGHT;
            setCursor(Qt::SizeFDiagCursor);
        }
    } else if (m_corner == BOTTOMLEFT) {
        if (m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() <= event->pos().x()) {
            m_corner = BOTTOMRIGHT;
            setCursor(Qt::SizeFDiagCursor);

        } else if (event->pos().y() <= m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()) {
            m_corner = TOPLEFT;
            setCursor(Qt::SizeFDiagCursor);
        }
    } else if (m_corner == BOTTOMRIGHT) {
        if (event->pos().x() <= m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()) {
            m_corner = BOTTOMLEFT;
            setCursor(Qt::SizeBDiagCursor);

        } else if (event->pos().y() <= m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()) {
            m_corner = TOPRIGHT;
            setCursor(Qt::SizeBDiagCursor);
        }
    }
}

void EllipseView::calculateResize(QGraphicsSceneMouseEvent *event)
{
    checkResizeRules(event);
    if (m_corner == TOPLEFT) {
        m_item->setRegisteredProperty(EllipseItem::P_WIDTH,
                                      m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                                      + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).
                                      toReal() - event->pos().x());

        m_item->setRegisteredProperty(EllipseItem::P_HEIGHT,
                                      m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                                      + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).
                                      toReal() - event->pos().y());

        m_item->setRegisteredProperty(EllipseItem::P_POSX, event->pos().x());
        m_item->setRegisteredProperty(EllipseItem::P_POSY, event->pos().y());

    }
    else if (m_corner == BOTTOMLEFT) {
        m_item->setRegisteredProperty(EllipseItem::P_WIDTH,
                                      m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                                      + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal()
                                      - event->pos().x());
        m_item->setRegisteredProperty(EllipseItem::P_HEIGHT, event->pos().y()
                                      - m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal());
        m_item->setRegisteredProperty(EllipseItem::P_POSX, event->pos().x());

    }
    else if (m_corner == TOPRIGHT) {
        m_item->setRegisteredProperty(EllipseItem::P_WIDTH, event->pos().x()
                                      - m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal());
        m_item->setRegisteredProperty(EllipseItem::P_HEIGHT,
                                      m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                                      + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT)
                                      .toReal() - std::abs(event->pos().y()));
        m_item->setRegisteredProperty(EllipseItem::P_POSY, event->pos().y());
    }
    else if (m_corner == BOTTOMRIGHT) {
        m_item->setRegisteredProperty(EllipseItem::P_WIDTH, event->pos().x()
                                      - m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal());
        m_item->setRegisteredProperty(EllipseItem::P_HEIGHT, event->pos().y()
                                      - m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal());
    }
}

qreal EllipseView::getRotationAngle(QGraphicsSceneMouseEvent *event)
{
    QPointF middlePoint
        = mapToScene(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                     + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() / 2,
                     m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                     + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() / 2);
    qreal lengthOfHypotenuse
        = sqrt(pow(m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() / 2, 2)
               + pow(m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() / 2, 2));
    qreal offsetAngle = acos((m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() / 2)
                             / lengthOfHypotenuse) * 180 / M_PI;
    qreal radians = atan((event->scenePos().y() - middlePoint.y())
                         / (event->scenePos().x() - middlePoint.x()));

    if (m_corner == TOPLEFT) {
        m_item->setRegisteredProperty(EllipseItem::P_ANGLE, radians * 180 / M_PI - offsetAngle);
        return radians * 180 / M_PI - offsetAngle;

    } else if (m_corner == TOPRIGHT) {
        m_item->setRegisteredProperty(EllipseItem::P_ANGLE, radians * 180 / M_PI + offsetAngle - 180);
        return radians * 180 / M_PI + offsetAngle - 180;

    } else if (m_corner == BOTTOMLEFT) {
        m_item->setRegisteredProperty(EllipseItem::P_ANGLE, radians * 180 / M_PI + offsetAngle - 180);
        return  radians * 180 / M_PI + offsetAngle - 180;

    } else if (m_corner == BOTTOMRIGHT) {
        m_item->setRegisteredProperty(EllipseItem::P_ANGLE, radians * 180 / M_PI - offsetAngle);
        return radians * 180 / M_PI - offsetAngle;
    }
    return 0.0;
}

void EllipseView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setFlag(QGraphicsItem::ItemIsMovable, false);

    if (event->button() == Qt::LeftButton) {
        setSelectedCorner(event->pos());

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

void EllipseView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // check which mode is active and process with the active mode
    if (m_mode == RESIZE && m_corner != NONE) {
        calculateResize(event);
    } else if (m_corner != NONE && m_mode == ROTATION) {
        QTransform transform;
        transform.translate(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                            + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() * 0.5,
                            m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                            + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() * 0.5);
        transform.rotate(getRotationAngle(event));
        transform.translate(-(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                              + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() * 0.5),
                            -(m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                              + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() * 0.5));
        setTransform(transform);
//         process as usual
    } else {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void EllipseView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // set all modes off, change cursor and process as usual
    m_corner = NONE;
    setCursor(Qt::ArrowCursor);
    QGraphicsItem::mouseReleaseEvent(event);
}

void EllipseView::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    setSelectedCorner(event->pos());
    m_corner = NONE;
}

void EllipseView::setInclude()
{
    m_item->setRegisteredProperty(EllipseItem::P_COLOR, 0);
}

void EllipseView::setExclude()
{
    m_item->setRegisteredProperty(EllipseItem::P_COLOR, 1);
}

QRectF EllipseView::getTopLeftCorner()
{
    return QRectF(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal() - OffsetPosition,
                  m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal() - OffsetPosition,
                  widthAndHeight, widthAndHeight);
}

QRectF EllipseView::getTopRightCorner()
{
    return QRectF(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                  + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() - OffsetPosition,
                  m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal() - OffsetPosition,
                  widthAndHeight, widthAndHeight);
}

QRectF EllipseView::getBottomLeftCorner()
{
    return QRectF(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal() - OffsetPosition,
                  m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                  + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() - OffsetPosition,
                  widthAndHeight, widthAndHeight);
}

QRectF EllipseView::getBottomRightCorner()
{
    return QRectF(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                  + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() - OffsetPosition,
                  m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                  + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() - OffsetPosition,
                  widthAndHeight, widthAndHeight);
}

void EllipseView::setParameterizedItem(ParameterizedItem *item)
{
    m_item = item;
//    setX(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
//         + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() * 0.5);
//    setY(m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
//         + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() * 0.5);
    setRotation(m_item->getRegisteredProperty(EllipseItem::P_ANGLE).toReal());
    connect(m_item, SIGNAL(propertyChanged(const QString &)), this,
            SLOT(onPropertyChange(const QString &)));
    initializeArrow();
}

void EllipseView::onChangedX()
{
//    m_block_update = true;
//    qDebug() << "onXValueChanged(double xValue)-> x value changed" << x();
//    m_item->setRegisteredProperty(EllipseItem::P_POSX, x());
//    m_block_update = false;
}

void EllipseView::onChangedY()
{
//    m_block_update = true;
//    qDebug() << "onYValueChanged(double yValue)-> y value changed" << y();
//    m_item->setRegisteredProperty(EllipseItem::P_POSY, y());
//    m_block_update = false;
}

void EllipseView::onPropertyChange(const QString &propertyName)
{
    if(propertyName == EllipseItem::P_ANGLE) {
    QTransform transform;
    transform.translate(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                        + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() * 0.5,
                        m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                        + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() * 0.5);
    transform.rotate(m_item->getRegisteredProperty(EllipseItem::P_ANGLE).toReal());
    transform.translate(-(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                          + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() * 0.5),
                        -(m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                          + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() * 0.5));
    setTransform(transform);
    }

}

ParameterizedItem *EllipseView::getParameterizedItem()
{
    return m_item;
}

void EllipseView::setSelectedCorner(QPointF currentMousePosition)
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

void EllipseView::updateRotationArrows()
{
    // 0 - 3 are rotation arrows
    childItems()[0]->setPos(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal(),
                            m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal());

    childItems()[1]->setPos(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal() +
                          m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal(),
                          m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal());

    childItems()[2]->setPos(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal(),
                          m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal() +
                          m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal());

    childItems()[3]->setPos(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal() +
                            m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal(),
                            m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal() +
                            m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal());

    // 4 - 7 are resize arrows
    childItems()[4]->setPos(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal(),
                            m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal());

    childItems()[5]->setPos(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal() +
                          m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal(),
                          m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal());

    childItems()[6]->setPos(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal(),
                          m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal() +
                          m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal());

    childItems()[7]->setPos(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal() +
                            m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal(),
                            m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal() +
                            m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal());


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

void EllipseView::initializeArrow()
{
    RotationArrow *topLeftRotationArrow = new RotationArrow(this);
    RotationArrow *topRightRotationArrow = new RotationArrow(this);
    RotationArrow *bottomLeftRotationArrow = new RotationArrow(this);
    RotationArrow *bottomRightRotationArrow = new RotationArrow(this);

    ResizeArrow *topLeftResizeArrow = new ResizeArrow(this);
    ResizeArrow *topRightResizeArrow = new ResizeArrow(this);
    ResizeArrow *bottomLeftResizeArrow = new ResizeArrow(this);
    ResizeArrow *bottomRightResizeArrow = new ResizeArrow(this);




    topLeftRotationArrow->setPos(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal(),
                         m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal());

    topRightRotationArrow->setRotation(90);
    topRightRotationArrow->setPos(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal() +
                          m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal(),
                          m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal() +
                          m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal());

    bottomLeftRotationArrow->setRotation(270);
    bottomLeftRotationArrow->setPos(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal(),
                            m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal() +
                            m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal());

    bottomRightRotationArrow->setRotation(180);
    bottomLeftRotationArrow->setPos(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal() +
                            m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal(),
                            m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal() +
                            m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal());


    topLeftResizeArrow->setPos(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal(),
                         m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal());

    topRightResizeArrow->setRotation(90);
    topRightResizeArrow->setPos(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal() +
                          m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal(),
                          m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal() +
                          m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal());

    bottomLeftResizeArrow->setRotation(270);
    bottomLeftResizeArrow->setPos(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal(),
                            m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal() +
                            m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal());

    bottomRightResizeArrow->setRotation(180);
    bottomLeftResizeArrow->setPos(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal() +
                            m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal(),
                            m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal() +
                            m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal());



    topRightRotationArrow->setVisible(false);
    topLeftRotationArrow->setVisible(false);
    bottomLeftRotationArrow->setVisible(false);
    bottomRightRotationArrow->setVisible(false);

    topRightResizeArrow->setVisible(false);
    topLeftResizeArrow->setVisible(false);
    bottomLeftResizeArrow->setVisible(false);
    bottomRightResizeArrow->setVisible(false);
}
