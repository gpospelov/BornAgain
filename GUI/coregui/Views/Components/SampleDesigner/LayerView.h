#ifndef LAYERVIEW_H
#define LAYERVIEW_H

#include "ILayerView.h"


//! Class that represents view of Layer
class BA_CORE_API_ LayerView : public ILayerView
{
    Q_OBJECT
public:
    enum { TYPE = DesignerHelper::LAYER };

    LayerView(QGraphicsItem *parent = 0);
    ~LayerView() { }

    int type() const { return TYPE; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void addView(IView *childView, int row = 0); // to add ParticleLayout

};


#endif // LAYERVIEW_H
