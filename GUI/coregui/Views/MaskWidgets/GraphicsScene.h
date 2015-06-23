#include <QWidget>
#include <QGraphicsProxyWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainterPath>
#include <QBrush>

#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

class Rectangle;
class Ellipse;
class Polygon;
class RectangleItem;
class RectangleView;
class MaskModel;
class ParameterizedItem;

#include <QModelIndex>

class GraphicsScene : public QGraphicsScene
{

public:
    GraphicsScene();
    enum Drawing { NONE, RECTANGLE, ELLIPSE, POLYGON };
    void setDrawing(Drawing drawing);

    void setMaskModel(MaskModel *maskModel);

protected:
    void updateScene();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void drawForeground(QPainter *painter, const QRectF &);

private:
    void updateViews(const QModelIndex &parentIndex = QModelIndex());
    QGraphicsItem *addViewForItem(ParameterizedItem *item);


    MaskModel *m_maskModel;
    Drawing m_drawing;
    Rectangle *m_rectangle;
    ParameterizedItem *m_rectangleItem;
    RectangleView *m_rectangleView;
    Ellipse *m_ellipse;
    Polygon *m_polygon;
    bool isFinished;
    QPointF m_currentMousePosition;
    QPointF m_lastAddedPoint;
};
#endif
