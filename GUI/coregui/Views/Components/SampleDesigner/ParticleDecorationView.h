#ifndef PARTICLEDECORATIONVIEW_H
#define PARTICLEDECORATIONVIEW_H

#include "ConnectableView.h"

class ParticleDecorationView : public ConnectableView
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName )

public:
    enum { Type = DesignerHelper::ParticleDecorationType };

    ParticleDecorationView(QGraphicsItem *parent = 0);

    //! сalls the ISampleViewVisitor's visit method
    virtual void accept(IViewVisitor *visitor) { visitor->visit(this); }

    int type() const { return Type; }

};


#endif // PARTICLEDECORATIONVIEW_H
