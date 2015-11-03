#include "ObsoleteRectangleView.h"
#include "RectangleItem.h"
#include "ParameterizedItem.h"
#include "DesignerHelper.h"
#include "ObsoleteRotationArrow.h"
#include "ObsoleteResizeArrow.h"
#include <QPainterPath>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <cmath>
#include <QCursor>

static const qreal widthAndHeight = 5;
static const qreal OffsetPosition = 2.5;


ObsoleteRectangleView::ObsoleteRectangleView() :
    m_diagonalOpposedPoint(new QPointF)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
    connect(this, SIGNAL(xChanged()), this, SLOT(onChangedX()));
    connect(this, SIGNAL(yChanged()), this, SLOT(onChangedY()));
}

void ObsoleteRectangleView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
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

    // change color
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

        updateArrows();
}

QRectF ObsoleteRectangleView::boundingRect() const
{
        return QRectF(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal() -5,
                      m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() -5,
                      m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() + 10,
                      m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() + 10);
}

void ObsoleteRectangleView::setDiagonalOpposedPoint()
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

void ObsoleteRectangleView::calculateResize(QGraphicsSceneMouseEvent *event)
{
        qreal xmin = std::min(event->pos().x(),m_diagonalOpposedPoint->x());
        qreal xmax = std::max(event->pos().x(),m_diagonalOpposedPoint->x());
        qreal ymin = std::min(event->pos().y(),m_diagonalOpposedPoint->y());
        qreal ymax = std::max(event->pos().y(),m_diagonalOpposedPoint->y());

        m_item->setRegisteredProperty(RectangleItem::P_WIDTH, xmax - xmin);
        m_item->setRegisteredProperty(RectangleItem::P_HEIGHT, ymax - ymin);

        m_item->setRegisteredProperty(RectangleItem::P_POSX, xmin);
        m_item->setRegisteredProperty(RectangleItem::P_POSY, ymin);
}

qreal ObsoleteRectangleView::getRotationAngle(QGraphicsSceneMouseEvent *event)
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

void ObsoleteRectangleView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setFlag(QGraphicsItem::ItemIsMovable, false);

    if (event->button() == Qt::LeftButton) {
        setSelectedCorner(event->pos());

        if (m_corner == NONE) {
            this->setFlag(QGraphicsItem::ItemIsMovable, true);
            m_block_mode = false;
            QGraphicsItem::mousePressEvent(event);
        }
        else {
            setDiagonalOpposedPoint();
        }
    }

}

void ObsoleteRectangleView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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
        transform.rotate(getRotationAngle(event));
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

void ObsoleteRectangleView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
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

void ObsoleteRectangleView::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    setSelectedCorner(event->pos());
    m_corner = NONE;
}

void ObsoleteRectangleView::setInclude()
{
    m_item->setRegisteredProperty(RectangleItem::P_COLOR, 0);
}

void ObsoleteRectangleView::setExclude()
{
    m_item->setRegisteredProperty(RectangleItem::P_COLOR, 1);
}


QRectF ObsoleteRectangleView::getTopLeftCorner()
{
    return QRectF(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal() - OffsetPosition,
                  m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() - OffsetPosition,
                  widthAndHeight, widthAndHeight);
}

QRectF ObsoleteRectangleView::getTopRightCorner()
{
    return QRectF(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal()
                  + m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() - OffsetPosition,
                  m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() - OffsetPosition,
                  widthAndHeight, widthAndHeight);
}

QRectF ObsoleteRectangleView::getBottomLeftCorner()
{
    return QRectF(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal() - OffsetPosition,
                  m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal()
                  + m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() - OffsetPosition,
                  widthAndHeight, widthAndHeight);
}

QRectF ObsoleteRectangleView::getBottomRightCorner()
{
    return QRectF(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal()
                  + m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() - OffsetPosition,
                  m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal()
                  + m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() - OffsetPosition,
                  widthAndHeight, widthAndHeight);
}

void ObsoleteRectangleView::setParameterizedItem(ParameterizedItem *item)
{
    m_item = item;
    setRotation(m_item->getRegisteredProperty(RectangleItem::P_ANGLE).toReal());
    connect(m_item, SIGNAL(propertyChanged(const QString &)), this,
            SLOT(onPropertyChange(const QString &)));
    initializeArrows();
}

void ObsoleteRectangleView::onChangedX()
{
    m_block_mode = true;
}

void ObsoleteRectangleView::onChangedY()
{
    m_block_mode = true;
}

void ObsoleteRectangleView::onPropertyChange(const QString &propertyName)
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

ParameterizedItem *ObsoleteRectangleView::getParameterizedItem()
{
    return m_item;
}

void ObsoleteRectangleView::setSelectedCorner(QPointF currentMousePosition)
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

void ObsoleteRectangleView::updateArrows()
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

void ObsoleteRectangleView::initializeArrows()
{
    ObsoleteRotationArrow *topLeftRotationArrow = new ObsoleteRotationArrow(this);
    ObsoleteRotationArrow *topRightRotationArrow = new ObsoleteRotationArrow(this);
    ObsoleteRotationArrow *bottomLeftRotationArrow = new ObsoleteRotationArrow(this);
    ObsoleteRotationArrow *bottomRightRotationArrow = new ObsoleteRotationArrow(this);

    ObsoleteResizeArrow *topLeftResizeArrow = new ObsoleteResizeArrow(this);
    ObsoleteResizeArrow *topRightResizeArrow = new ObsoleteResizeArrow(this);
    ObsoleteResizeArrow *bottomLeftResizeArrow = new ObsoleteResizeArrow(this);
    ObsoleteResizeArrow *bottomRightResizeArrow = new ObsoleteResizeArrow(this);


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



