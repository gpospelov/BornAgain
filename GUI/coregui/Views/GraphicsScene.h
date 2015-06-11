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

class GraphicsScene : public QGraphicsScene
{

public:
    GraphicsScene();
    enum Drawing { NONE, RECTANGLE, ELLIPSE, POLYGON };
    void setDrawing(Drawing drawing);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void drawForeground(QPainter *painter, const QRectF &);


private:
    Drawing m_drawing;
    Rectangle *m_rectangle;
    Ellipse *m_ellipse;
    Polygon *m_polygon;
    bool isFinished;
    QPointF m_currentMousePosition;
    QPointF m_lastAddedPoint;
};
#endif
