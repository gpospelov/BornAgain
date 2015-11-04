#ifndef OBSOLETEELLIPSEITEM_H
#define OBSOLETEELLIPSEITEM_H

#include "ParameterizedItem.h"

class ObsoleteEllipseItem : public ParameterizedItem
{
        Q_OBJECT

public:
    static const QString P_POSX;
    static const QString P_POSY;
    static const QString P_WIDTH;
    static const QString P_HEIGHT;
    static const QString P_COLOR;
    static const QString P_ANGLE;

    explicit ObsoleteEllipseItem(ParameterizedItem *parent=0);
    ~ObsoleteEllipseItem(){}
};

#endif
