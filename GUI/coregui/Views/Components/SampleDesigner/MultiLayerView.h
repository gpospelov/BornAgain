#ifndef MULTILAYERVIEW_H
#define MULTILAYERVIEW_H


#include "ILayerView.h"

class DesignerMimeData;
class QGraphicsSceneDragDropEvent;

//! Class representing view of MultiLayer.
//! Handles drop of other MultiLayer and Layer views on top of it
class BA_CORE_API_ MultiLayerView : public ILayerView
{
    Q_OBJECT

public:
    enum { TYPE = DesignerHelper::MULTILAYER };

    MultiLayerView(QGraphicsItem *parent = 0);

    int type() const { return TYPE; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void addView(IView *childView, int row = 0);

    virtual void addNewLayer(ILayerView *layer, int row);
    virtual void removeLayer(ILayerView *layer);

    bool isInDropArea(QPointF pos);
    int getDropArea(QPointF pos);
    QRectF getDropAreaRectangle(int row);
    QLineF getInterfaceLine(int row);

public slots:
    void updateGeometry();
    void updateHeight();
    void updateWidth();
    void onLayerAboutToBeDeleted();

protected:
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    const DesignerMimeData *checkDragEvent(QGraphicsSceneDragDropEvent * event);

private:
    QList<ILayerView *> m_layers;
    QList<QRectF> m_drop_areas;
    QList<QLineF> m_interfaces;
};


#endif // MULTILAYERVIEW_H
