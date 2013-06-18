#ifndef PARTICLEDECORATIONVIEW_H
#define PARTICLEDECORATIONVIEW_H

#include "ISampleView.h"

class ParticleDecorationView : public ISampleRectView
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName )

public:
    enum { Type = DesignerHelper::ParticleDecorationType };

    ParticleDecorationView(QGraphicsItem *parent = 0);

    int type() const { return Type; }

};


#endif // PARTICLEDECORATIONVIEW_H
