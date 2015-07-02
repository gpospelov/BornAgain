#ifndef POLYGONITEM_H
#define POLYGONITEM_H

#include "ParameterizedItem.h"

class PolygonItem : public ParameterizedItem
{
        Q_OBJECT

public:
    static const QString P_COLOR;
    static const QString P_DRAWINGMODE;

    explicit PolygonItem(ParameterizedItem *parent=0);
    ~PolygonItem(){}
};

#endif
