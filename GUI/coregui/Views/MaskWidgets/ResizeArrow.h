#ifndef RESIZEARROW_H
#define RESIZEARROW_H

#include <QGraphicsItem>

class ResizeArrow : public QGraphicsItem
{
public:
    ResizeArrow(QGraphicsItem *parent = 0);

    //! bounding box of rectangle
    QRectF boundingRect() const;

protected:
    //! paintEvent paints Rectangle and corners
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
};




#endif
