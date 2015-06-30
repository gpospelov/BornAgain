#ifndef RECTANGLEITEM_H
#define RECTANGLEITEM_H

#include "ParameterizedItem.h"
//#include "RectangleView.h"

class RectangleItem : public ParameterizedItem
{
        Q_OBJECT

public:
    static const QString P_POSX;
    static const QString P_POSY;
    static const QString P_WIDTH;
    static const QString P_HEIGHT;
    static const QString P_COLOR;

    explicit RectangleItem(ParameterizedItem *parent=0);
    ~RectangleItem(){}
};

#endif
