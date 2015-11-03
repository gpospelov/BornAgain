#ifndef OBSOLETERESIZEARROW_H
#define OBSOLETERESIZEARROW_H

#include <QGraphicsItem>

class ObsoleteResizeArrow : public QGraphicsItem
{
public:
    ObsoleteResizeArrow(QGraphicsItem *parent = 0);

    //! bounding box of rectangle
    QRectF boundingRect() const;

protected:
    //! paintEvent paints Rectangle and corners
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
};




#endif
