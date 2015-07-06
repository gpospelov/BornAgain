#ifndef ROTATIONARROW_H
#define ROTATIONARROW_H

#include <QGraphicsItem>

class RotationArrow : public QGraphicsItem
{
public:
    RotationArrow(QGraphicsItem *parent = 0);

    //! bounding box of rectangle
    QRectF boundingRect() const;

protected:
    //! paintEvent paints Rectangle and corners
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
};

#endif
