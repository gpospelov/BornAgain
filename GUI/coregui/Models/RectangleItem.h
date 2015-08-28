#ifndef RECTANGLEITEM_H
#define RECTANGLEITEM_H

#include "ParameterizedItem.h"

class RectangleItem : public ParameterizedItem
{
        Q_OBJECT

public:
    static const QString P_POSX;
    static const QString P_POSY;
    static const QString P_WIDTH;
    static const QString P_HEIGHT;
    static const QString P_COLOR;
    static const QString P_ANGLE;

    explicit RectangleItem(ParameterizedItem *parent=0);
    ~RectangleItem(){}
};

#endif
