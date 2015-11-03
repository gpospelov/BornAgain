#ifndef OBSOLETEROTATIONARROW_H
#define OBSOLETEROTATIONARROW_H

#include <QGraphicsItem>

class ObsoleteRotationArrow : public QGraphicsItem
{
public:
    ObsoleteRotationArrow(QGraphicsItem *parent = 0);

    //! bounding box of rectangle
    QRectF boundingRect() const;

protected:
    //! paintEvent paints Rectangle and corners
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
};




#endif
