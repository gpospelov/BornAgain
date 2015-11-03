#include "ObsoleteResizeArrow.h"
#include <QPainter>


ObsoleteResizeArrow::ObsoleteResizeArrow(QGraphicsItem *parent)
{
    this->setParentItem(parent);
}

QRectF ObsoleteResizeArrow::boundingRect() const
{
    return QRect(-25,-25,20,20);
}


void ObsoleteResizeArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing);
    prepareGeometryChange();

    QPainterPath upperArrowHead;
    upperArrowHead.moveTo(-20, -20);
    upperArrowHead.lineTo(-17.5, -12.5);
    upperArrowHead.lineTo(-12.5, -17.5);
    upperArrowHead.lineTo(-20, -20);
    painter->fillPath(upperArrowHead, Qt::black);

    QPainterPath lowerArrowHead;
    lowerArrowHead.moveTo(-7.5, -7.5);
    lowerArrowHead.lineTo(-10, -15);
    lowerArrowHead.lineTo(-15, -10);
    lowerArrowHead.lineTo(-7.5, -7.5);
    painter->fillPath(lowerArrowHead, Qt::black);

    QPen pen;
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawLine(QPointF(-17.5, -17.5), QPointF(-10,-10));



}
