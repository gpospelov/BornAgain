#ifndef PARTICLECORESHELLVIEW_H
#define PARTICLECORESHELLVIEW_H

#include "ConnectableView.h"

//! Class representing view of Particle item
class BA_CORE_API_ ParticleCoreShellView : public ConnectableView
{
    Q_OBJECT

public:
    enum { TYPE = DesignerHelper::PARTICLE };

    ParticleCoreShellView(QGraphicsItem *parent = 0);

    int type() const { return TYPE; }

    void addView(IView *childView, int row = 0);

};


#endif

