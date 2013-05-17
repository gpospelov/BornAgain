#include "ISampleView.h"
#include "DesignerHelper.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

ISampleDefaultView::ISampleDefaultView(QGraphicsItem *parent)
    : ISampleView(parent)
    , m_rect(0, 0, DesignerHelper::getLayerWidth(), DesignerHelper::getLayerHeight())
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}


QRectF ISampleDefaultView::boundingRect() const
{
    return rect();
}


void ISampleDefaultView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setPen(Qt::black);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }

    painter->setBrush(DesignerHelper::getLayerGradient(Qt::gray, rect() ) );
    painter->drawRect(rect());
}




//ISampleView::ISampleView(QGraphicsItem *parent)
//    : QGraphicsPolygonItem(parent)
//{

//    m_polygon << QPointF(-40, -20) << QPointF(40, -20) << QPointF(40, 20) << QPointF(-40, 20) << QPointF(-40, -20);

//    setPolygon(m_polygon);

//    setFlag(QGraphicsItem::ItemIsMovable, true);
//    setFlag(QGraphicsItem::ItemIsSelectable, true);
//    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
//}


