#ifndef POLYGONITEM_H
#define POLYGONITEM_H

#include "ParameterizedItem.h"

class PolygonItem : public ParameterizedItem
{
        Q_OBJECT

public:
    static const QString P_COLOR;
    static const QString P_DRAWINGMODE;
    static const QString P_MOUSEISOVERFIRSTPOINT;
    static const QString P_FIRSTPOINTXVALUE;
    static const QString P_FIRSTPOINTYVALUE;

    explicit PolygonItem(ParameterizedItem *parent=0);
    ~PolygonItem(){}


    int getColor();
    bool isDrawingMode();
    void setColor(int color);
    void setDrawingMode(bool drawingMode);
};

#endif
