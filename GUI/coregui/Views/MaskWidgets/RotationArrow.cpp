#include "RotationArrow.h"
#include <QPainter>


RotationArrow::RotationArrow(QGraphicsItem *parent)
{
    this->setParentItem(parent);
}

QRectF RotationArrow::boundingRect() const
{
    return QRect(-30,-30,100,100);
}


void RotationArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing);
    QPen pen;

   QPainterPath path;
   path.arcMoveTo(-20,-20,30,30,90);
   path.arcTo(-20,-20,30,30,90, 90);
   pen.setWidth(3);
   painter->setPen(pen);
   painter->drawPath(path);
   pen.setWidth(1);
   painter->setPen(pen);

   QPolygon polygon1;
   QPolygon polygon2;
   polygon1 << QPoint(-5,-25) << QPoint(-5, -15) << QPoint(0, -20);
   polygon2 << QPoint(-25,-5) << QPoint(-15, -5) << QPoint(-20, 0);

   QPainterPath fillColor1;
   fillColor1.moveTo(-5, -25);
   fillColor1.lineTo(-5, -15);
   fillColor1.lineTo(0, -20);
   painter->fillPath(fillColor1, Qt::black);

   QPainterPath fillColor2;
   fillColor2.moveTo(-25, -5);
   fillColor2.lineTo(-15, -5);
   fillColor2.lineTo(-20, 0);
   painter->fillPath(fillColor2, Qt::black);
   painter->drawPolygon(polygon1);
   painter->drawPolygon(polygon2);

}
