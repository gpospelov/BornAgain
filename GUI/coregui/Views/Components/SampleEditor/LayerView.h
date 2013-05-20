#ifndef LAYERVIEW_H
#define LAYERVIEW_H

#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QColor>
#include <QRectF>
#include <QRect>
#include <QGradient>

#include "ISampleView.h"

class LayerView : public ISampleView
{
    Q_OBJECT

public:

    LayerView(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRect rect() const { return m_rect; }

    void setFixedX() { m_fixed_xpos = x(); }
    qreal getFixedX() { return m_fixed_xpos; }

Q_SIGNALS:
    void LayerMoved();


protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dropEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event);

private:
    QColor m_color;
    QRect m_rect;
    qreal m_fixed_xpos;
};



#endif // LAYERVIEW_H
