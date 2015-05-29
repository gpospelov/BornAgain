#include "DistributionEditor.h"


#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

class GraphicsProxyWidget: public QGraphicsProxyWidget
{
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif
