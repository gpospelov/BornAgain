#ifndef INTERFERENCEFUNCTION1DPARACRYSTALVIEW_H
#define INTERFERENCEFUNCTION1DPARACRYSTALVIEW_H


#include "ISampleView.h"

class InterferenceFunction1DParaCrystalView : public ISampleRectView
{
public:
    InterferenceFunction1DParaCrystalView(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};


#endif // INTERFERENCEFUNCTION1DPARACRYSTALVIEW_H

