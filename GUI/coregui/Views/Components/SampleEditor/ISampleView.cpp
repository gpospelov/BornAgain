#include "ISampleView.h"
#include "DesignerHelper.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>


ISampleDefaultView::ISampleDefaultView(QGraphicsItem *parent)
    : ISampleView(parent)
    , m_rect(0, 0, DesignerHelper::getDefaultLayerWidth()/2, DesignerHelper::getDefaultLayerWidth()/2)
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

