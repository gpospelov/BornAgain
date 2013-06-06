#ifndef LAYERDOCKVIEW_H
#define LAYERDOCKVIEW_H

#include "ISampleView.h"

#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QColor>
#include <QRectF>
#include <QRect>
#include <QGradient>

class LayerView;
class MultiLayerView;
class DesignerMimeData;


class LayerDockView : public ISampleView
{
    Q_OBJECT
public:

    LayerDockView(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRect rect() const { return m_rect; }



    void addLayer(LayerView *layer, QPointF pos=QPointF());
    void addLayer(MultiLayerView *layer, QPointF pos=QPointF());

public slots:
    void updateHeight();

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);


    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    const DesignerMimeData *checkDragEvent(QGraphicsSceneDragDropEvent * event);
private:
    bool isInDropArea(QPointF pos);

    QColor m_color;
    QRect m_rect;
    QLine m_line;
    QList<QRectF> m_drop_areas;
};



#endif // LAYERDOCKVIEW_H
