#ifndef HOMOGENEOUSLAYERVIEW_H
#define HOMOGENEOUSLAYERVIEW_H

#include <QGraphicsItem>
#include <QColor>
#include <QRectF>
#include <QRect>
#include <QGradient>

class HomogeneousLayerView : public QGraphicsItem
{
public:

    HomogeneousLayerView();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRect rect() const { return m_rect; }

protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QGradient gradient(const QColor &color, const QRect &rect);

private:
    QColor m_color;
    QRect m_rect;
};



#endif // HOMOGENEOUSLAYERVIEW_H
