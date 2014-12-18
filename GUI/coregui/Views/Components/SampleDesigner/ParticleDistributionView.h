#ifndef PARTICLEDISTRIBUTIONVIEW_H
#define PARTICLEDISTRIBUTIONVIEW_H

#include "ConnectableView.h"

//! Class representing view of distributed particle item
class BA_CORE_API_ ParticleDistributionView : public ConnectableView
{
    Q_OBJECT

public:
    enum { Type = DesignerHelper::ParticleType };

    ParticleDistributionView(QGraphicsItem *parent = 0);

    int type() const { return Type; }

    void addView(IView *childView, int row = 0);

};


#endif

