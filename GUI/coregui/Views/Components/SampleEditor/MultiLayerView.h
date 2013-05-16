#ifndef MULTILAYERVIEW_H
#define MULTILAYERVIEW_H

#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QColor>
#include <QRectF>
#include <QRect>
#include <QGradient>

class LayerView;

class DesignerMimeData;

class MultiLayerView : public QGraphicsObject
{
    Q_OBJECT
public:

    MultiLayerView(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRect rect() const { return m_rect; }

public slots:
    void updateHeight();

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);


//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    const DesignerMimeData *checkDragEvent(QGraphicsSceneDragDropEvent * event);


    void addLayer(LayerView *layer, QPointF pos=QPointF());
private:
    bool isInDropArea(QPointF pos);

    QColor m_color;
    QRect m_rect;
    QLine m_line;
    QList<QRectF> m_drop_areas;
};



#endif // MULTILAYERVIEW_H
