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

EllipseView::EllipseView() : m_diagonalOpposedPoint(new QPointF)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
    connect(this, SIGNAL(xChanged()), this, SLOT(onChangedX()));
    connect(this, SIGNAL(yChanged()), this, SLOT(onChangedY()));
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
    updateArrows();
}

QRectF EllipseView::boundingRect() const
{
    return QRectF(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal() - 5,
                  m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal() - 5,
                  m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() + 10,
                  m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() + 10);
}

void EllipseView::setDiagonalOpposedPoint()
{
    if (m_corner == TOPLEFT) {
        m_diagonalOpposedPoint->setX(getBottomRightCorner().x());
        m_diagonalOpposedPoint->setY(getBottomRightCorner().x());
    } else if (m_corner == TOPRIGHT) {
        m_diagonalOpposedPoint->setX(getBottomLeftCorner().x());
        m_diagonalOpposedPoint->setY(getBottomLeftCorner().y());
    } else if (m_corner == BOTTOMLEFT) {
        m_diagonalOpposedPoint->setX(getTopRightCorner().x());
        m_diagonalOpposedPoint->setY(getTopRightCorner().y());
    } else if (m_corner == BOTTOMRIGHT) {
        m_diagonalOpposedPoint->setX(getTopLeftCorner().x());
        m_diagonalOpposedPoint->setY(getTopLeftCorner().y());
    }
}

void EllipseView::calculateResize(QGraphicsSceneMouseEvent *event)
{
        qreal xmin = std::min(event->pos().x(),m_diagonalOpposedPoint->x());
        qreal xmax = std::max(event->pos().x(),m_diagonalOpposedPoint->x());
        qreal ymin = std::min(event->pos().y(),m_diagonalOpposedPoint->y());
        qreal ymax = std::max(event->pos().y(),m_diagonalOpposedPoint->y());

        m_item->setRegisteredProperty(EllipseItem::P_WIDTH, xmax - xmin);
        m_item->setRegisteredProperty(EllipseItem::P_HEIGHT, ymax - ymin);

        m_item->setRegisteredProperty(EllipseItem::P_POSX, xmin);
        m_item->setRegisteredProperty(EllipseItem::P_POSY, ymin);
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
            this->setFlag(QGraphicsItem::ItemIsMovable, true);
            QGraphicsItem::mousePressEvent(event);
        }
        else {
            setDiagonalOpposedPoint();
        }
    }
}

void EllipseView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_corner == NONE) {
        m_block_mode = true;
    }

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
    if(!m_block_mode) {
        if (m_mode == RESIZE) {
            m_mode = ROTATION;
        } else if (m_mode == ROTATION) {
            m_mode = RESIZE;
        }
    }
    m_block_mode = false;
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
    setRotation(m_item->getRegisteredProperty(EllipseItem::P_ANGLE).toReal());
    connect(m_item, SIGNAL(propertyChanged(const QString &)), this,
            SLOT(onPropertyChange(const QString &)));
    initializeArrows();
}

void EllipseView::onChangedX()
{
    m_block_mode = true;
}

void EllipseView::onChangedY()
{
    m_block_mode = true;
}

void EllipseView::onPropertyChange(const QString &propertyName)
{
    if(propertyName == EllipseItem::P_POSX) {
         m_block_mode = true;
    }
    else if(propertyName == EllipseItem::P_POSY) {
         m_block_mode = true;
    }
    else if(propertyName == EllipseItem::P_ANGLE) {
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

void EllipseView::updateArrows()
{
    // 0 - 3 are rotation arrows
    childItems()[0]->setPos(getTopLeftCorner().x(), getTopLeftCorner().y());
    childItems()[1]->setPos(getTopRightCorner().x(), getTopRightCorner().y());
    childItems()[2]->setPos(getBottomLeftCorner().x(), getBottomLeftCorner().y());
    childItems()[3]->setPos(getBottomRightCorner().x(), getBottomRightCorner().y());

    // 4 - 7 are resize arrows
    childItems()[4]->setPos(getTopLeftCorner().x(), getTopLeftCorner().y());
    childItems()[5]->setPos(getTopRightCorner().x(), getTopRightCorner().y());
    childItems()[6]->setPos(getBottomLeftCorner().x(), getBottomLeftCorner().y());
    childItems()[7]->setPos(getBottomRightCorner().x(), getBottomRightCorner().y());


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

void EllipseView::initializeArrows()
{
    RotationArrow *topLeftRotationArrow = new RotationArrow(this);
    RotationArrow *topRightRotationArrow = new RotationArrow(this);
    RotationArrow *bottomLeftRotationArrow = new RotationArrow(this);
    RotationArrow *bottomRightRotationArrow = new RotationArrow(this);

    ResizeArrow *topLeftResizeArrow = new ResizeArrow(this);
    ResizeArrow *topRightResizeArrow = new ResizeArrow(this);
    ResizeArrow *bottomLeftResizeArrow = new ResizeArrow(this);
    ResizeArrow *bottomRightResizeArrow = new ResizeArrow(this);

    topRightRotationArrow->setRotation(90);
    bottomLeftRotationArrow->setRotation(270);
    bottomRightRotationArrow->setRotation(180);

    topRightResizeArrow->setRotation(90);
    bottomLeftResizeArrow->setRotation(270);
    bottomRightResizeArrow->setRotation(180);

    topRightRotationArrow->setVisible(false);
    topLeftRotationArrow->setVisible(false);
    bottomLeftRotationArrow->setVisible(false);
    bottomRightRotationArrow->setVisible(false);

    topRightResizeArrow->setVisible(false);
    topLeftResizeArrow->setVisible(false);
    bottomLeftResizeArrow->setVisible(false);
    bottomRightResizeArrow->setVisible(false);
}
