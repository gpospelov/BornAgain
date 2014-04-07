#ifndef LAYERVIEW_H
#define LAYERVIEW_H

//#include "ConnectableView.h"
#include "ILayerView.h"


//class MultiLayerView;

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

//protected:
//    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

//public slots:
//    void onPropertyChange(QString propertyName);

//private:
//    MultiLayerView * m_requested_parent;
//    //! Possible parent (MultiLayer) encountered during  the movement of the Layer across the scene.
//    int m_requested_row;
//    //! possible row to drop the layer in  encountered MultiLayer
//    QPointF m_drag_start_position;
};



#endif // LAYERVIEW_H
