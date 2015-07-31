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

   QPainterPath path;
   path.arcMoveTo(-20,-20,10,10,90);
   path.arcTo(-20,-20,10,10,90, 90);
   pen.setWidth(2);
   painter->setPen(pen);
   painter->drawPath(path);
   pen.setWidth(1);
   painter->setPen(pen);

//   QPolygon polygon1;
//   QPolygon polygon2;
//   polygon1 << QPoint(-15,-20) << QPoint(-15, -15) << QPoint(-10, -17.5);
//   polygon2 << QPoint(-20,-15) << QPoint(-15, -15) << QPoint(-17.5, -10);

   QPainterPath fillColor1;
   fillColor1.moveTo(-15, -25);
   fillColor1.lineTo(-15, -15);
   fillColor1.lineTo(-10, -20);
   painter->fillPath(fillColor1, Qt::black);

   QPainterPath fillColor2;
   fillColor2.moveTo(-25, -15);
   fillColor2.lineTo(-15, -15);
   fillColor2.lineTo(-20, -10);
   painter->fillPath(fillColor2, Qt::black);
//   painter->drawPolygon(polygon1);
//   painter->drawPolygon(polygon2);

//   painter->drawRect(boundingRect());

}
