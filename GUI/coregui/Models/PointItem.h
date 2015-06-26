#ifndef POINTITEM_H
#define POINTITEM_H

#include "ParameterizedItem.h"

class PointItem : public ParameterizedItem
{
    Q_OBJECT

public:
    static const QString P_POSX;
    static const QString P_POSY;

    explicit PointItem(ParameterizedItem *parent = 0);
    ~PointItem()
    {
    }

    qreal getXPos();
    qreal getYPos();
    void setXPos(qreal xPos);
    void setYPos(qreal yPos);
};

#endif
