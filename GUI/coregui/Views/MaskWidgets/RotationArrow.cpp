#include "RotationArrow.h"
#include <QPainter>


RotationArrow::RotationArrow(QGraphicsItem *parent)
{
    this->setParentItem(parent);
}

QRectF RotationArrow::boundingRect() const
{
    return QRect(-25,-25,15,15);
}


void RotationArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing);
    prepareGeometryChange();
    QPen pen;

   QPainterPath lineBetweenArrowHeads;
   lineBetweenArrowHeads.arcMoveTo(-20,-20,10,10,90);
   lineBetweenArrowHeads.arcTo(-20,-20,10,10,90, 90);
   pen.setWidth(2);
   painter->setPen(pen);
   painter->drawPath(lineBetweenArrowHeads);
   pen.setWidth(1);
   painter->setPen(pen);


   QPainterPath upperArrowHead;
   upperArrowHead.moveTo(-15, -25);
   upperArrowHead.lineTo(-15, -15);
   upperArrowHead.lineTo(-10, -20);
   painter->fillPath(upperArrowHead, Qt::black);

   QPainterPath lowerArrowHead;
   lowerArrowHead.moveTo(-25, -15);
   lowerArrowHead.lineTo(-15, -15);
   lowerArrowHead.lineTo(-20, -10);
   painter->fillPath(lowerArrowHead, Qt::black);

}
