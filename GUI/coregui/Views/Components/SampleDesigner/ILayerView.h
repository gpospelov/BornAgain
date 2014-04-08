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
    MultiLayerCandidate getMultiLayerCandidate();

//    MultiLayerView * m_requested_parent;
//    //!< Possible parent (MultiLayer) encountered during  the movement of the
//    //!< Layer across the scene.

//    int m_requested_row;
//    //! requested row to drop the layer in  encountered MultiLayer

    QPointF m_drag_start_position;
};


//! Class to hold MultiLayer candidate for dropping LayerView.
class MultiLayerCandidate
{
public:
    MultiLayerCandidate() : multilayer(0), row(-1), distance(0){}
    MultiLayerView *multilayer; //!< pointer to the candidate
    int row; //!< requested row number to drop in
    int distance; //!< distance from given ILayerView and drop area
    //QRectF getSceneDropArea();
    QLineF getInterfaceToScene();
    bool operator< (const MultiLayerCandidate& cmp) const;
    operator bool() const { return bool(multilayer); }
};


#endif
