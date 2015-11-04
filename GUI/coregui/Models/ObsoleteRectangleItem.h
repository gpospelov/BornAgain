#ifndef OBSOLETERECTANGLEITEM_H
#define OBSOLETERECTANGLEITEM_H

#include "ParameterizedItem.h"

class ObsoleteRectangleItem : public ParameterizedItem
{
        Q_OBJECT

public:
    static const QString P_POSX;
    static const QString P_POSY;
    static const QString P_WIDTH;
    static const QString P_HEIGHT;
    static const QString P_COLOR;
    static const QString P_ANGLE;

    explicit ObsoleteRectangleItem(ParameterizedItem *parent=0);
    ~ObsoleteRectangleItem(){}
};

#endif
