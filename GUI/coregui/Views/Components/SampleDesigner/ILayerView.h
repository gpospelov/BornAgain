#ifndef ILAYERVIEW_H
#define ILAYERVIEW_H

#include "ConnectableView.h"


class MultiLayerView;
class MultiLayerCandidate;

//! Base class for LayerView and MultiLayerView
//! Provides functionality for moving view on top of MultiLayer.
class ILayerView : public ConnectableView
{
    Q_OBJECT
public:

    ILayerView(QGraphicsItem *parent = 0);

    enum { Type = DesignerHelper::LayerType };

    int type() const { return Type; }

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void onPropertyChange(QString propertyName);

private:
    void findMultiLayerCandidate();

    MultiLayerView * m_requested_parent; //! Possible parent (MultiLayer) encountered during  the movement of the Layer across the scene.
    int m_requested_row; //! possible row to drop the layer in  encountered MultiLayer
    QPointF m_drag_start_position;
};


#endif
