#ifndef PARTICLECORESHELLVIEW_H
#define PARTICLECORESHELLVIEW_H

#include "ConnectableView.h"

//! Class representing view of Particle item
class ParticleCoreShellView : public ConnectableView
{
    Q_OBJECT

public:
    enum { Type = DesignerHelper::ParticleType };

    ParticleCoreShellView(QGraphicsItem *parent = 0);

    int type() const { return Type; }
};


#endif

