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
    static const QString P_RESIZEMODE;
    static const QString P_ROTATIONMODE;
    static const QString P_COLOR;

    explicit EllipseItem(ParameterizedItem *parent=0);
    ~EllipseItem(){}

    qreal getXPos();
    qreal getYPos();
    qreal getWidth();
    qreal getHeight();
    bool isResizeMode();
    bool isRotationMode();
    int getColor();
    void setXPos(qreal xPos);
    void setYPos(qreal yPos);
    void setWidth(qreal width);
    void setHeight(qreal height);
    void setResizeMode(bool resizeMode);
    void setRotationMode(bool rotationMode);
    void setColor(int color);
};

#endif
