#ifndef ELLIPSEITEM_H
#define ELLIPSEITEM_H

#include "ParameterizedItem.h"

class EllipseItem : public ParameterizedItem
{
        Q_OBJECT

public:
    static const QString P_POSX;
    static const QString P_POSY;
    static const QString P_WIDTH;
    static const QString P_HEIGHT;
    static const QString P_COLOR;

    explicit EllipseItem(ParameterizedItem *parent=0);
    ~EllipseItem(){}
};

#endif
