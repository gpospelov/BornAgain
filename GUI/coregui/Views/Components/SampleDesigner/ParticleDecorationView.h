#ifndef PARTICLEDECORATIONVIEW_H
#define PARTICLEDECORATIONVIEW_H

#include "ISampleView.h"

class ParticleDecorationView : public ISampleRectView
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName )

public:
    ParticleDecorationView(QGraphicsItem *parent = 0);

};


#endif // PARTICLEDECORATIONVIEW_H
