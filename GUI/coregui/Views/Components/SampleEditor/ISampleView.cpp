#include "ISampleView.h"



ISampleView::ISampleView(QGraphicsItem *parent)
    : QGraphicsPolygonItem(parent)
{

    m_polygon << QPointF(-40, -20) << QPointF(40, -20) << QPointF(40, 20) << QPointF(-40, 20) << QPointF(-40, -20);

    setPolygon(m_polygon);

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}


