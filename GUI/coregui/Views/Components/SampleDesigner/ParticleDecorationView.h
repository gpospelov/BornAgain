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

    //! сalls the ISampleViewVisitor's visit method
    virtual void accept(ISampleViewVisitor *visitor) const { visitor->visit(this); }

    int type() const { return Type; }

};


#endif // PARTICLEDECORATIONVIEW_H
