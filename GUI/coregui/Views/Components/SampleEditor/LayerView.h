#ifndef LAYERVIEW_H
#define LAYERVIEW_H

#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QColor>
#include <QRectF>
#include <QRect>
#include <QGradient>

class LayerView : public QGraphicsObject
{
    Q_OBJECT

public:

    LayerView(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRect rect() const { return m_rect; }

    void setFixedX() { m_fixed_xpos = x(); }

Q_SIGNALS:
    void LayerMoved();


protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);

private:
    QColor m_color;
    QRect m_rect;
    qreal m_fixed_xpos;
};



#endif // LAYERVIEW_H
