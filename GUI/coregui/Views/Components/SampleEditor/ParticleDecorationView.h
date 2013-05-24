#ifndef PARTICLEDECORATIONVIEW_H
#define PARTICLEDECORATIONVIEW_H

#include "ISampleView.h"

class ParticleDecorationView : public ISampleRectView
{
public:
    ParticleDecorationView(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};


#endif // PARTICLEDECORATIONVIEW_H
