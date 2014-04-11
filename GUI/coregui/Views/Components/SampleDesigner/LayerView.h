#ifndef LAYERVIEW_H
#define LAYERVIEW_H

#include "ILayerView.h"


//! Class that represents view of Layer
class LayerView : public ILayerView
{
    Q_OBJECT
public:
    enum { Type = DesignerHelper::LayerType };

    LayerView(QGraphicsItem *parent = 0);
    ~LayerView() { }

    int type() const { return Type; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void addView(IView *childView, int row = 0); // to add ParticleLayout
};


#endif // LAYERVIEW_H
