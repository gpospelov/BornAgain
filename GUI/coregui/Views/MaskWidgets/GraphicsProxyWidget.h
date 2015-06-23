#include "DistributionEditor.h"


#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

class GraphicsProxyWidget: public QGraphicsProxyWidget
{
public:
        enum {Type = UserType + 4};
        int type() const {return Type;}
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif
