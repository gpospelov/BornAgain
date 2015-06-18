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
//    static const QString P_TOPLEFTCORNER;
//    static const QString P_TOPRIGHTCORNER;
//    static const QString P_BOTTOMLEFTCORNER;
//    static const QString P_BOTTOMRIGHTCORNER;
    static const QString P_RESIZEMODE;
    static const QString P_ROTATIONMODE;
    static const QString P_COLOR;

    explicit RectangleItem(ParameterizedItem *parent=0);
    ~RectangleItem(){}

    qreal getXPos();
    qreal getYPos();
    qreal getWidth();
    qreal getHeight();
    bool isResizeMode();
    bool isRotationMode();
    void setXPos(qreal xPos);
    void setYPos(qreal yPos);
    void setWidth(qreal width);
    void setHeight(qreal height);
    void setResizeMode(bool resizeMode);
    void setRotationMode(bool rotationMode);
//    void setColor(RectangleView::Color color);

};

#endif
