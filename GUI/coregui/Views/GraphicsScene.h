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
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
//    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
//    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
//    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    Drawing m_drawing;
    Rectangle *m_rectangle;
    Ellipse *m_ellipse;
    Polygon *m_polygon;
};
#endif
