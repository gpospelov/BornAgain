#ifndef OBSOLETEPOLYGONITEM_H
#define OBSOLETEPOLYGONITEM_H

#include "ParameterizedItem.h"

class ObsoletePolygonItem : public ParameterizedItem
{
        Q_OBJECT

public:
    static const QString P_COLOR;
    static const QString P_DRAWINGMODE;

    explicit ObsoletePolygonItem(ParameterizedItem *parent=0);
    ~ObsoletePolygonItem(){}
};

#endif
