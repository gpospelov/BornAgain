#ifndef OBSOLETEPOINTITEM_H
#define OBSOLETEPOINTITEM_H

#include "ParameterizedItem.h"

class ObsoletePointItem : public ParameterizedItem
{
    Q_OBJECT

public:
    static const QString P_POSX;
    static const QString P_POSY;

    explicit ObsoletePointItem(ParameterizedItem *parent = 0);
    ~ObsoletePointItem()
    {
    }

    qreal getXPos();
    qreal getYPos();
    void setXPos(qreal xPos);
    void setYPos(qreal yPos);
};

#endif
