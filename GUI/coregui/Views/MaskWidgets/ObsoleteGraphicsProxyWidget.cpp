#include "ObsoleteGraphicsProxyWidget.h"



void ObsoleteGraphicsProxyWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsProxyWidget::mousePressEvent(event);
    event->accept();
}

void ObsoleteGraphicsProxyWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsProxyWidget::mouseReleaseEvent(event);
}


void ObsoleteGraphicsProxyWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsProxyWidget::mouseMoveEvent(event);
}
