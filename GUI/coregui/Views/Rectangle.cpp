#include "Rectangle.h"

Rectangle::Rectangle(qreal posX, qreal posY, qreal width, qreal heigth)
    : m_posX(posX)
    , m_posY(posY)
    , m_width(width)
    , m_heigth(heigth)
    , m_topLeftCorner(new QGraphicsRectItem(m_posX-5, m_posY-5, 10, 10))
    , m_bottomLeftCorner(new QGraphicsRectItem(m_posX + m_width -5, m_posY-5, 10, 10))
    , m_topRightCorner(new QGraphicsRectItem(m_posX + m_width -5, m_posY-5, 10, 10))
    , m_bottomRightCorner(new QGraphicsRectItem(m_posX + m_width -5, m_posY + m_heigth -5, 10, 10))
    , m_resizeMode(false)
{
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->cursor().setShape(Qt::ClosedHandCursor);
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    delete m_topLeftCorner;
    delete m_topRightCorner;
    delete m_bottomLeftCorner;
    delete m_bottomRightCorner;

    this->prepareGeometryChange();
    painter->drawRect(m_posX, m_posY, m_width, m_heigth);

    if(this->isSelected()) {
        painter->setBrush(Qt::green);
        this->prepareGeometryChange();
        painter->drawRect(m_posX-5, m_posY-5, 10, 10);
        this->prepareGeometryChange();
        painter->drawRect(m_posX + m_width -5, m_posY-5, 10, 10);
        this->prepareGeometryChange();
        painter->drawRect(m_posX-5, m_posY + m_heigth -5, 10, 10);
        this->prepareGeometryChange();
        painter->drawRect(m_posX + m_width -5, m_posY + m_heigth -5, 10, 10);
    }
    m_topLeftCorner = new QGraphicsRectItem(m_posX-5, m_posY-5, 10, 10);
    m_bottomLeftCorner = new QGraphicsRectItem(m_posX-5, m_posY + m_heigth -5, 10, 10);
    m_topRightCorner = new QGraphicsRectItem(m_posX + m_width -5, m_posY-5, 10, 10);
    m_bottomRightCorner = new QGraphicsRectItem(m_posX + m_width -5, m_posY + m_heigth -5, 10, 10);

}

QRectF Rectangle::boundingRect() const
{
    return QRectF(m_posX-10, m_posY-10  , m_width+50, m_heigth+50);
}

void Rectangle::checkResizeRules(QGraphicsSceneMouseEvent *event)
{
    if(m_corner == TOPLEFT) {
        if(m_topLeftCorner->pos().x() <= event->pos().x()) {
            m_corner = TOPRIGHT;
        }
        else if(m_bottomLeftCorner->pos().y() <= event->pos().y()) {
            m_corner = BOTTOMLEFT;
        }
    }
    else if(m_corner == TOPRIGHT) {
        if(event->pos().x() <= m_topLeftCorner->pos().x())
            m_corner = TOPLEFT;
        else if(m_bottomRightCorner->pos().y() <= event->pos().y()) {
            m_corner = BOTTOMRIGHT;
        }
    }
    else if(m_corner == BOTTOMLEFT) {
        if(m_bottomRightCorner->pos().x() <= event->pos().x()) {
            m_corner = BOTTOMRIGHT;
        }
        else if(event->pos().y() <= m_bottomRightCorner->pos().y()) {
            m_corner = TOPLEFT;
        }
    }
    else if(m_corner == BOTTOMRIGHT) {
        if(event->pos().x() <= m_bottomRightCorner->pos().x()) {
            m_corner = BOTTOMLEFT;
        }
        else if(event->pos().y() <= m_bottomRightCorner->pos().y()) {
            m_corner = TOPRIGHT;
        }
    }
}

void Rectangle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && m_topLeftCorner->contains(event->pos())) {
        m_resizeMode = true;
        m_corner = TOPLEFT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        this->cursor().setShape(Qt::ClosedHandCursor);
    }
    else if(event->button() == Qt::LeftButton &&  m_bottomLeftCorner->contains(event->pos())) {
        m_resizeMode = true;
         m_corner = BOTTOMLEFT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        this->cursor().setShape(Qt::ClosedHandCursor);
    }
    else if(event->button() == Qt::LeftButton &&  m_topRightCorner->contains(event->pos())) {
        m_resizeMode = true;
        m_corner = TOPRIGHT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        this->cursor().setShape(Qt::ClosedHandCursor);
    }

    else if(event->button() == Qt::LeftButton &&  m_bottomRightCorner->contains(event->pos())) {
        m_resizeMode = true;
        m_corner = BOTTOMRIGHT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        this->cursor().setShape(Qt::ClosedHandCursor);
    }

    else {
        m_resizeMode = false;
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mousePressEvent(event);
    }
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
}

void Rectangle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_corner == TOPLEFT && m_resizeMode) {
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        checkResizeRules(event);
        m_width = m_topRightCorner->pos().x() - event->pos().x();
        m_heigth = m_bottomLeftCorner->pos().y() - event->pos().y();
        m_posX = event->pos().x();
        m_posY = event->pos().y();


    }
    else if(m_corner == BOTTOMLEFT && m_resizeMode) {
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        checkResizeRules(event);
        m_width = m_bottomRightCorner->pos().x() - event->pos().x();
        m_heigth = event->pos().y() - m_topLeftCorner->pos().y();
        m_posX = event->pos().x();
        m_posY = event->pos().y() - m_heigth;
    }
    else if(m_corner == TOPRIGHT && m_resizeMode) {
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        checkResizeRules(event);
        m_width = event->pos().x() - m_topLeftCorner->pos().x() ;
        m_heigth = m_bottomRightCorner->pos().y() - event->pos().y();
        m_posX = event->pos().x() - m_width;
        m_posY = event->pos().y();
    }

    else if(m_corner == BOTTOMRIGHT && m_resizeMode) {
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        checkResizeRules(event);
        m_width =  event->pos().x() - m_bottomLeftCorner->pos().x();
        m_heigth = event->pos().y() - m_topRightCorner->pos().y();
        m_posX = event->pos().x() - m_width;
        m_posY = event->pos().y() - m_heigth;
    }
    else {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mouseMoveEvent(event);
    }
    this->setFlag(QGraphicsItem::ItemIsMovable, true);

}

void Rectangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    QGraphicsItem::mouseReleaseEvent(event);
}
