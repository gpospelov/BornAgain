#ifndef PARTICLEVIEW_H
#define PARTICLEVIEW_H


#include "ConnectableView.h"


//! Class representing view of Particle item
class ParticleView : public ConnectableView
{
    Q_OBJECT

public:
    enum { Type = DesignerHelper::FormFactorType };

    ParticleView(QGraphicsItem *parent = 0);

    int type() const { return Type; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};



#endif
